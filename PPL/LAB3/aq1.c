#include <mpi.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char* argv []) {

    int rank, size;
    int i, m,sendBuf[100],recvBuf[100],final[200];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0){
        printf("Enter the M value:");
        scanf("%d",&m);
        int n=size;
        printf("Enter %d elements: ", m * n);
        for (i = 0; i < m * n; ++i) 
            scanf("%d", &sendBuf[i]);
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(sendBuf, m, MPI_INT, recvBuf, m, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank%2==0){
        for(i=0;i<m;i++)
            recvBuf[i]=recvBuf[i]*recvBuf[i];
        
    }
    if(rank%2!=0){
        for(i=0;i<m;i++)
            recvBuf[i]=recvBuf[i]*recvBuf[i]*recvBuf[i];
        
    }
    MPI_Gather(&recvBuf, m, MPI_INT, final, m, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank==0){
        printf("The final values are:");
        for(i=0;i<m*size;i++){
            printf("%d \t",final[i]);
        }
    }
}   