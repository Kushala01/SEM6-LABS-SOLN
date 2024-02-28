#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define MCW MPI_COMM_WORLD

int main(int argc, char ** argv){
    MPI_Init(&argc,&argv);
    int rank,size,num;
    MPI_Status status;
    MPI_Comm_rank(MCW,&rank);
    MPI_Comm_size(MCW,&size);
    int arr[size];
    if(rank==0){
        printf("\n enter %d elements for the array\n",size);
        for(int i=0;i<size;i++){
            scanf("%d",&arr[i]);
        }int buffer_size=MPI_BSEND_OVERHEAD+size*sizeof(int);
        int buffer[buffer_size];
        MPI_Buffer_attach(buffer,buffer_size);
        for(int i=0;i<size;i++){
            MPI_Bsend(&arr[i],1,MPI_INT,i,100+i,MCW);
        }MPI_Buffer_detach(&buffer,&buffer_size);
    }else{
        MPI_Recv(&num,1,MPI_INT,0,100+rank,MCW,&status);
        if(rank%2==0)
            printf("At process %d: val after square is: %d\n",rank,num*num);
        else
            printf("At process %d: val after cube is: %d\n",rank,num*num*num);
    }MPI_Finalize();
    return 0;
}