// transpose of matrix

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 1024

// row-wise - NOT DONE
__global__ void multa(int *a, int* b, int *t, int n, int p) {
    int ridx = threadIdx.x;
    int m = blockDim.x;

    for(int j=0; j<n; j++)
        for(int k=0; k<p; k++)
            t[ridx*ncol+i] = a[ridx*ncol+i] + b[ridx*ncol+i];
  
}

// // column-wise
// __global__ void multb(int *a, int* b, int *t, int nrow) {
//     int cidx = threadIdx.x;
//     int ncol = blockDim.x;

//     for(int i=0; i<nrow; i++)
//         t[cidx+ncol*i] = a[cidx+ncol*i] + b[cidx+ncol*i];
  
// }

// // element-wise
// __global__ void multc(int *a, int* b, int *t) {
//     int eidx = threadIdx.x;
//     t[eidx] = a[eidx] + b[eidx];
// }

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
    int m, n, p, i;
    int *da, *db, *dt;

    printf("Enter number of rows and columns of A: ");
    scanf("%d %d", &m, &p);
    printf("Enter number of columns of B: ");
    scanf("%d", &n);

    int sizea = sizeof(int)*m*p;
    int sizeb = sizeof(int)*p*n;
    int sizet = sizeof(int)*m*n;

    a = (int*)malloc(sizea);
    b = (int*)malloc(sizeb);
    t = (int*)malloc(sizet);

    printf("Enter %d elements of the matrix A: \n",m*p);
    for(i=0;i<m*p;i++)
        scanf("%d", &a[i]);

    printf("\nEnter %d elements of the matrix B: \n",p*n);
    for(i=0;i<p*n;i++)
        scanf("%d", &b[i]);

    cudaMalloc((void**)&da, sizea);
    cudaMalloc((void**)&db, sizeb);
    cudaMalloc((void**)&dt, sizet);
    cudaMemcpy(da, a, sizea, cudaMemcpyHostToDevice);
    cudaMemcpy(db, b, sizeb, cudaMemcpyHostToDevice);
    cudaMemcpy(dt, t, sizet, cudaMemcpyHostToDevice);

    // ROW-WISE
    multa<<<1,m>>>(da, db, dt, n, p); 

    cudaMemcpy(t, dt, sizet, cudaMemcpyDeviceToHost);
    printf("\nA) Row-wise multiplication:\n");
    display(m,n,t);
    cudaFree(dt);

    // cudaMalloc((void**)&dt, size);
    // cudaMemcpy(dt, t, size, cudaMemcpyHostToDevice);

    // // COLUMN-WISE
    // multb<<<1,c>>>(da, db, dt, r);
    
    // cudaMemcpy(t, dt, size, cudaMemcpyDeviceToHost);
    // printf("\nB) Column-wise multiplication:\n");
    // display(r,c,t);
    // cudaFree(dt);

    // cudaMalloc((void**)&dt, size);
    // cudaMemcpy(dt, t, size, cudaMemcpyHostToDevice);
    
    // // ELEMENT-WISE
    // multc<<<1,r*c>>>(da, db, dt);
    
    // cudaMemcpy(t, dt, size, cudaMemcpyDeviceToHost);
    // printf("\nC) Element-wise multiplication:\n");
    // display(r,c,t);
    // cudaFree(dt);

    cudaFree(da);
    cudaFree(db);
    
    return 0;
}
