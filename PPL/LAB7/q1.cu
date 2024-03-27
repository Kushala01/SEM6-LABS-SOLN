#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 1024

__global__ void countOccurrences(char* str, char* w, int* result, int length, int wn) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < length) {
        if (tid + wn <= length) {
            bool match = true;
            for (int i = 0; i < wn; i++) {
                if (str[tid + i] != w[i]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                atomicAdd(result, 1);
            }
        }
    }
}

int main() {
    char a[N];
    char w[N];

    printf("Enter a string: ");
    scanf("%[^\n]s", a);
    printf("Enter a word: ");
    scanf("%s", w);

    int an = strlen(a);
    int wn = strlen(w);

    char* da;
    char* dw;
    int* dres;

    cudaMalloc((void**)&da, an * sizeof(char));
    cudaMalloc((void**)&dw, wn * sizeof(char));
    cudaMalloc((void**)&dres, sizeof(int));

    cudaMemcpy(da, a, an * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(dw, w, wn * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemset(dres, 0, sizeof(int));

    int block_size = 32;
    int num_blocks = (an + block_size - 1) / block_size;

    countOccurrences<<<num_blocks, block_size>>>(da, dw, dres, an, wn);

    int result;
    cudaMemcpy(&result, dres, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Occurrences of the '%s' is %d\n",w,result);

    cudaFree(da);
    cudaFree(dw);
    cudaFree(dres);

    return 0;
}
