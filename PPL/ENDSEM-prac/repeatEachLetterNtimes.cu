#include <stdio.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#define MAX_LENGTH 256  // Maximum length of input and output strings

__global__ void repeatStringKernel(const char* input, char* output, int length) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    int index = tid * 3;  // Each character in input is repeated three times

    if (tid < length) {
        for (int i = 0; i < 3; i++) {
            output[index + i] = input[tid];  // Repeat the character three times
        }
    }
}

int main() {
    char input[MAX_LENGTH];
    char output[MAX_LENGTH * 3];  // Output string can be up to three times the input length
    char *d_input, *d_output;
    int length;

    printf("Enter a string: ");
    scanf("%s", input);

    length = strlen(input);

    cudaMalloc((void**)&d_input, length * sizeof(char));
    cudaMalloc((void**)&d_output, length * 3 * sizeof(char));  // Allocate space for output

    cudaMemcpy(d_input, input, length * sizeof(char), cudaMemcpyHostToDevice);

    int blockSize = 256;  // Threads per block
    int gridSize = (length + blockSize - 1) / blockSize;  // Calculate grid size

    repeatStringKernel<<<gridSize, blockSize>>>(d_input, d_output, length);

    cudaMemcpy(output, d_output, length * 3 * sizeof(char), cudaMemcpyDeviceToHost);

    printf("Input string: %s\n", input);
    printf("Output string: %s\n", output);

    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}
