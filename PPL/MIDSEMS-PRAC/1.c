#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#define MCW MPI_COMM_WORLD

void error(int ierr){
	int resultlen, errclass;
	char err_buffer[MPI_MAX_ERROR_STRING];
	MPI_Error_class(ierr, &errclass);
	MPI_Error_string(ierr,err_buffer,&resultlen);
	if(ierr!=MPI_SUCCESS){
		fprintf(stderr,"error class %d-%s",ierr,err_buffer);
		MPI_Finalize();
		exit(1);
	}
}
int findFact(int n){
	int val=1;
	for(int i=2;i<=n;i++)
		val*=i;
	return val;
}
int main(int argc, char**argv){
	int rank, size,ierr,soln;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MCW,&rank);
	MPI_Comm_size(MCW,&size);
	MPI_Errhandler_set(MCW,MPI_ERRORS_RETURN);
	int fact=findFact(rank+1);
	ierr=MPI_Scan(&fact,&soln,1,MPI_INT,MPI_SUM,MCW);
	error(ierr);
	if(rank==size-1){
		printf("%d",soln);
	}
	MPI_Finalize();
	return 0;
}