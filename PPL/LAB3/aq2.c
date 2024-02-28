#include <mpi.h>
#include <stdio.h>
#include <string.h>


void main(int argc, char* argv []) {

    int rank, size,n;
    int i, m,sendBuf[100],recvBuf[100],final[200];
    int odd=0,even=0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0){
        printf("Enter the number of elements:");
        scanf("%d",&n);
        printf("Enter the elements:\n");
        for(i = 0; i < n; ++i) 
            scanf("%d", &sendBuf[i]);
        m=n/size;
    }
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(sendBuf, m, MPI_INT, recvBuf, m, MPI_INT, 0, MPI_COMM_WORLD);
    for(i=0;i<m;i++){
        if(recvBuf[i]%2==0){//even
            recvBuf[i]=1;
        }
        else{
            recvBuf[i]=0;
        }
    }
    MPI_Gather(&recvBuf, m, MPI_INT, final, m, MPI_INT, 0, MPI_COMM_WORLD);
    if(rank==0){
        printf("The final values are:");
        for(i=0;i<n;i++){
            if(final[i]==0)
                odd++;
            else if(final[i]==1)
                even++;
            printf("%d \t",final[i]);
        }
        printf("The even count is:%d",even);
        printf("The odd count is:%d",odd);
    }
}