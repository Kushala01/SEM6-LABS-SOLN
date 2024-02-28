#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define MCW MPI_COMM_WORLD

int main(int argc, char ** argv){
	int rank,size,val;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MCW,&rank);
	MPI_Comm_size(MCW,&size);
	if(rank==0){
		printf("\nenter a number:\n");
		scanf("%d",&val);
		val++;
		MPI_Send(&val,1,MPI_INT,1,101,MCW);
		MPI_Recv(&val,1,MPI_INT,size-1,99,MCW,&status);
		printf("At process: %d and val is: %d\n",rank,val);

	}else{
		if(rank==size-1){
			MPI_Recv(&val,1,MPI_INT,rank-1,100+rank,MCW,&status);
			val+=1;
			MPI_Send(&val,1,MPI_INT,0,99,MCW);
		}
		MPI_Recv(&val,1,MPI_INT,rank-1,100+rank,MCW,&status);
		val+=1;
		//printf("At process: %d and val is: %d\n",rank,val);
		MPI_Send(&val,1,MPI_INT,rank+1,100+rank+1,MCW);
	}
}