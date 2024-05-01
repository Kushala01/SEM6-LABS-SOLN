#include <stdio.h>

__global__ void inclusiveScan(int *input, int *output, int n) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    if (tid >= n) return;

    // Perform parallel reduction (up-sweep phase)
    for (int stride = 1; stride < n; stride *= 2) {
        int index = 2 * stride * (tid + 1) - 1;
        if (index < n) {
            input[index] += input[index - stride];
        }
        __syncthreads();
    }

    // Clear the last element to prepare for down-sweep phase
    if (tid == 0) {
        input[n - 1] = 0;
    }
    __syncthreads();

    // Perform parallel reduction (down-sweep phase)
    for (int stride = n / 2; stride > 0; stride /= 2) {
        int index = 2 * stride * (tid + 1) - 1;
        if (index + stride < n) {
            input[index + stride] += input[index];
        }
        __syncthreads();
    }

    // Write the result back to global memory
    output[tid] = input[tid];
}

int main() {
    const int N = 8;
    const int block_size = 8;

    int input[N] = {3, 1, 7, 0, 4, 1, 6, 3};
    int output[N];

    int *d_input, *d_output;
    cudaMalloc(&d_input, N * sizeof(int));
    cudaMalloc(&d_output, N * sizeof(int));

    cudaMemcpy(d_input, input, N * sizeof(int), cudaMemcpyHostToDevice);

    inclusiveScan<<<1, block_size>>>(d_input, d_output, N);

    cudaMemcpy(output, d_output, N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Input array:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");

    printf("Inclusive Scan (Prefix Sum) Result:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}