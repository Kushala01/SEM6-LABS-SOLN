// transpose of matrix

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 1024

// row-wise
__global__ void adda(int *a, int* b, int *t, int ncol) {
    int ridx = threadIdx.x;

    for(int i=0; i<ncol; i++)
        t[ridx*ncol+i] = a[ridx*ncol+i] + b[ridx*ncol+i];
  
}

// column-wise
__global__ void addb(int *a, int* b, int *t, int nrow) {
    int cidx = threadIdx.x;
    int ncol = blockDim.x;

    for(int i=0; i<nrow; i++)
        t[cidx+ncol*i] = a[cidx+ncol*i] + b[cidx+ncol*i];
  
}

// element-wise
__global__ void addc(int *a, int* b, int *t) {
    int eidx = threadIdx.x;
    t[eidx] = a[eidx] + b[eidx];
}

void display(int r, int c, int *t)
{
    int i, j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("%d\t",t[i*c+j]);
            t[i*c+j] = 0;  // CLEARING THE RESULTANT MATRIX SIMULTANEOUSLY
        }   
        printf("\n");
    }
}

int main() 
{
    int *a, *b, *t;
    int r, c, i;
    int *da, *db, *dt;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &r, &c);

    int size = sizeof(int)*r*c;

    a = (int*)malloc(size);
    b = (int*)malloc(size);
    t = (int*)malloc(size);

    printf("Enter the elements of the matrix A: \n");
    for(i=0;i<r*c;i++)
        scanf("%d", &a[i]);

    printf("\nEnter the elements of the matrix B: \n");
    for(i=0;i<r*c;i++)
        scanf("%d", &b[i]);

    cudaMalloc((void**)&da, size);
    cudaMalloc((void**)&db, size);
    cudaMalloc((void**)&dt, size);
    cudaMemcpy(da, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(db, b, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dt, t, size, cudaMemcpyHostToDevice);

    // ROW-WISE
    adda<<<1,r>>>(da, db, dt, c);

    cudaMemcpy(t, dt, size, cudaMemcpyDeviceToHost);
    printf("\nA) Row-wise summation:\n");
    display(r,c,t);
    cudaFree(dt);

    cudaMalloc((void**)&dt, size);
    cudaMemcpy(dt, t, size, cudaMemcpyHostToDevice);

    // COLUMN-WISE
    addb<<<1,c>>>(da, db, dt, r);
    
    cudaMemcpy(t, dt, size, cudaMemcpyDeviceToHost);
    printf("\nB) Column-wise summation:\n");
    display(r,c,t);
    cudaFree(dt);

    cudaMalloc((void**)&dt, size);
    cudaMemcpy(dt, t, size, cudaMemcpyHostToDevice);
    
    // ELEMENT-WISE
    addc<<<1,r*c>>>(da, db, dt);
    
    cudaMemcpy(t, dt, size, cudaMemcpyDeviceToHost);
    printf("\nC) Element-wise summation:\n");
    display(r,c,t);
    cudaFree(dt);

    cudaFree(da);
    cudaFree(db);
    
    return 0;
}
