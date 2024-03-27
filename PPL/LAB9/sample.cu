// transpose of matrix

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 1024

__global__ void transpose(int *a, int *t) {
    int n = threadIdx.x;
    int m = blockIdx.x;
    int size = blockDim.x;
    int sizel = gridDim.x;

    t[n*sizel+m] = a[m*size+n];
  
}

int main() 
{
    int *a, *t, m, n, i, j;
    int *da, *dt;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &m, &n);

    int size = sizeof(int)*m*n;

    a = (int*)malloc(m*n*sizeof(int));
    t = (int*)malloc(m*n*sizeof(int));

    printf("Enter the elements of the matrix: \n");
    for(i=0;i<m*n;i++)
        scanf("%d", &a[i]);

    cudaMalloc((void**)&da, size);
    cudaMalloc((void**)&dt, size);

    cudaMemcpy(da, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dt, t, size, cudaMemcpyHostToDevice);

    transpose<<<m,n>>>(da, dt);

    cudaMemcpy(t, dt, size, cudaMemcpyDeviceToHost);

    printf("Result Vector is:\n");

    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            printf("%d\t",t[i*m+j]);
        printf("\n");
    }


    cudaFree(da);
    cudaFree(dt);

    return 0;
}
