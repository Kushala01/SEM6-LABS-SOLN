#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 1024

__global__ void CUDACount(char *a, unsigned int *dc)
{
    int i = threadIdx.x;
    if(a[i]=='a')
        atomicAdd(dc, 1);
}

int main()
{
    char a[N];
    char *da;
    unsigned int *dc;
    int res;
    printf("Enter a string: ");
    scanf("%s", a);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start, 0);

    cudaMalloc((void**)&da, strlen(a)*sizeof(char));
    cudaMalloc((void**)&dc, sizeof(unsigned int));

    cudaMemcpy(da, a, strlen(a)*sizeof(char), cudaMemcpyHostToDevice);

    cudaError_t err = cudaGetLastError();
    if(err!=cudaSuccess)
        printf("CUDA Error 1 : %s\n", cudaGetErrorString(err));
    
    CUDACount<<<1,strlen(a)>>>(da, dc);
    err = cudaGetLastError();
    if(err!=cudaSuccess)
        printf("CUDA Error 2 : %s\n", cudaGetErrorString(err));

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    float et;
    cudaEventElapsedTime(&et, start, stop);

    cudaMemcpy(&res, dc, sizeof(unsigned int), cudaMemcpyDeviceToHost);

    printf("Total occurences of a: %d", res);
    printf("\nTotal time taken: %f", et);

    cudaFree(da);
    cudaFree(dc);
    printf("\n");
    getchar();

    return 0;

}
