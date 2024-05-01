#include <cuda_runtime.h>
#include <stdlib.h>
#include <device_launch_parameters.h>
#include <stdio.h>

__global__ void SPMV_CSR(int *d_data, int *d_col_idx, int *d_row_ptr, int *d_res, int *d_matB, int rowNum) {
    int rowTid = blockIdx.x * blockDim.x + threadIdx.x;
    if (rowTid < rowNum) {
        int start = d_row_ptr[rowTid];
        int end = d_row_ptr[rowTid + 1];
        int sum = 0;
        for (int i = start; i < end; i++) {
            sum += d_data[i] * d_matB[d_col_idx[i]];
        }
        d_res[rowTid] = sum;
    }
}

int main() {
    int r1, c1;
    printf("\nEnter the size of row:\n");
    scanf("%d", &r1);
    printf("\nEnter the size of col:\n");
    scanf("%d", &c1);

    int *matA = (int *)malloc(r1 * c1 * sizeof(int));
    int *matB = (int *)malloc(r1 * sizeof(int));
    int *res = (int *)malloc(r1 * sizeof(int));

    printf("\nEnter the elements of matrix A:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            scanf("%d", &matA[i * c1 + j]);
        }
    }

    printf("\nEnter the elements of matrix B:\n");
    for (int i = 0; i < r1; i++) {
        scanf("%d", &matB[i]);
    }

    int nnz = 0;  // Number of non-zero elements in matA
    for (int i = 0; i < r1 * c1; i++) {
        if (matA[i] != 0) {
            nnz++;
        }
    }

    int *data = (int *)malloc(nnz * sizeof(int));
    int *col_idx = (int *)malloc(nnz * sizeof(int));
    int *row_ptr = (int *)malloc((r1 + 1) * sizeof(int));

    int k = 0;
    row_ptr[0] = 0;
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            if (matA[i * c1 + j] != 0) {
                data[k] = matA[i * c1 + j];
                col_idx[k] = j;
                k++;
            }
        }
        row_ptr[i + 1] = k;
    }

    int *d_data, *d_col_idx, *d_row_ptr, *d_res, *d_matB;
    cudaMalloc((void **)&d_data, nnz * sizeof(int));
    cudaMalloc((void **)&d_col_idx, nnz * sizeof(int));
    cudaMalloc((void **)&d_row_ptr, (r1 + 1) * sizeof(int));
    cudaMalloc((void **)&d_res, r1 * sizeof(int));
    cudaMalloc((void **)&d_matB, r1 * sizeof(int));

    cudaMemcpy(d_data, data, nnz * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_col_idx, col_idx, nnz * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_row_ptr, row_ptr, (r1 + 1) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_matB, matB, r1 * sizeof(int), cudaMemcpyHostToDevice);

    SPMV_CSR<<<(r1 + 255) / 256, 256>>>(d_data, d_col_idx, d_row_ptr, d_res, d_matB, r1);

    cudaMemcpy(res, d_res, r1 * sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nResultant matrix:\n");
    for (int i = 0; i < r1; i++) {
        printf("%d\n", res[i]);
    }

    cudaFree(d_res);
    cudaFree(d_data);
    cudaFree(d_col_idx);
    cudaFree(d_row_ptr);
    cudaFree(d_matB);

    free(matA);
    free(matB);
    free(res);
    free(data);
    free(col_idx);
    free(row_ptr);

    return 0;
}