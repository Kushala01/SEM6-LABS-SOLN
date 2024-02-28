#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define MCW MPI_COMM_WORLD

int main(int argc, char ** argv){
    MPI_Init(&argc,&argv);
    int rank,size;
    int num=23;
    MPI_Status status;
    MPI_Comm_rank(MCW,&rank);
    MPI_Comm_size(MCW,&size);
    if(rank==0){
        for(int i=0;i<size;i++){
            MPI_Send(&num,1,MPI_INT,i,100+i,MCW);
            printf("\nsent: %d to process %d\n",num,i);
        }
    }else{
        MPI_Recv(&num,1,MPI_INT,0,100+rank,MCW,&status);
        printf("\nProcess: %d received: %d\n",rank,num);
    }MPI_Finalize();
    return 0;
}