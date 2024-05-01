#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void MatMulElementThreadShared(int *a, int *b, int *c, int width, int block_width, int tile_width) {
    __shared__ int MDs[32][32];  
    __shared__ int NDs[32][32]; 
    int m;
    int bx = blockIdx.x;
    int by = blockIdx.y;
    int tx = threadIdx.x;
    int ty = threadIdx.y;
    int Row = by * tile_width + ty;
    int Col = bx * tile_width + tx;
    int Pvalue = 0;
    for (m = 0; m < width / tile_width; m++) {
        MDs[ty][tx] = a[Row * width + m * tile_width + tx];
        NDs[ty][tx] = b[(m * tile_width + ty) * width + Col];
        __syncthreads();
        for (int k = 0; k < tile_width; k++) {
            Pvalue += MDs[ty][k] * NDs[k][tx];
        }
        __syncthreads();
    }
    c[Row * width + Col] = Pvalue;
}

int main() {
    int width, block_width, tile_width;
    printf("Enter the width of the matrices: ");
    scanf("%d", &width);
    printf("Enter the block width: ");
    scanf("%d", &block_width);
    printf("Enter the tile width: ");
    scanf("%d", &tile_width);

    int *matA, *matB, *matProd;
    int *da, *db, *dc;

    matA = (int*)malloc(sizeof(int) * width * width);
    matB = (int*)malloc(sizeof(int) * width * width);
    matProd = (int*)malloc(sizeof(int) * width * width);

    printf("\n== Enter elements of Matrix A (%dx%d) ==\n", width, width);
    for (int i = 0; i < width * width; i++) {
        scanf("%d", &matA[i]);
    }

    printf("\n== Enter elements of Matrix B (%dx%d) ==\n", width, width);
    for (int i = 0; i < width * width; i++) {
        scanf("%d", &matB[i]);
    }

    cudaMalloc((void **)&da, sizeof(int) * width * width);
    cudaMalloc((void **)&db, sizeof(int) * width * width);
    cudaMalloc((void **)&dc, sizeof(int) * width * width);

    cudaMemcpy(da, matA, sizeof(int) * width * width, cudaMemcpyHostToDevice);
    cudaMemcpy(db, matB, sizeof(int) * width * width, cudaMemcpyHostToDevice);

    dim3 grid_conf(width / block_width, width / block_width);
    dim3 block_conf(block_width, block_width);

    MatMulElementThreadShared<<<grid_conf, block_conf>>>(da, db, dc, width, block_width, tile_width);

    cudaMemcpy(matProd, dc, sizeof(int) * width * width, cudaMemcpyDeviceToHost);

    printf("\n-=Result of Multiplication (%dx%d)=-\n", width, width);
    printf("-----------------------------------\n");
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            printf("%6d ", matProd[i * width + j]);
        }
        printf("\n");
    }

    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);
    free(matA);
    free(matB);
    free(matProd);

    return 0;
}