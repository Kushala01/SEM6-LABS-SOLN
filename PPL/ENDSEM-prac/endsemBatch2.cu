#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>

__device__ int position(char* str, int* row, int id) {
    int pos = 0;
    for (int i = 0; i < row[id]; i++) {
        if (str[id] == '+')
            pos += row[id] + 1;
        else
            pos += row[id] + 2;
    }
    return pos;
}

__global__ void sparse(char* str, char* res, int* row, int* col, int len) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id > len) return;
        int pos = position(str, row, id);
        if (str[id] == '+') {
            for (int i = pos; i < pos + row[id] + 1; i++)
                res[i] = str[id];
        } else {
            for (int i = pos; i < pos + row[id] + 2; i++)
                res[i] = str[id];
        }
}

int main() {
    char str[100], res[100];

    printf("Enter string: ");
    scanf("%s", str);
    int len = strlen(str);

    int row[len], col[len];

    printf("Enter row mat: ");
    for (int i = 0; i < len; i++)
        scanf("%d", &row[i]);

    printf("Enter col mat: ");
    for (int i = 0; i < len; i++)
        scanf("%d", &col[i]);

    int* d_row, *d_col;
    char* d_str, *d_res;

    cudaMalloc((void**)&d_str, len * sizeof(char));
    cudaMalloc((void**)&d_res, len * len * sizeof(char)); // Assuming maximum possible length for result
    cudaMalloc((void**)&d_row, len * sizeof(int));
    cudaMalloc((void**)&d_col, len * sizeof(int));

    cudaMemcpy(d_str, str, len * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_res, res, len * len * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_row, row, len * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_col, col, len * sizeof(int), cudaMemcpyHostToDevice);

    int numOfThreads = 256;
    int numOfBlocks = (len + numOfThreads - 1) / numOfThreads; // Adjusted block count

    sparse<<<numOfBlocks, numOfThreads>>>(d_str, d_res, d_row, d_col, len);

    cudaMemcpy(res, d_res, len * len * sizeof(char), cudaMemcpyDeviceToHost);

    printf("Result: %s\n", res);

    cudaFree(d_str);
    cudaFree(d_res);
    cudaFree(d_row);
    cudaFree(d_col);

    return 0;
}