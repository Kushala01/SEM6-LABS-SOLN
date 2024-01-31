#include "mpi.h"
#include<stdio.h>
#define MCW MPI_COMM_WORLD

void error(int ierr){
	int errclass,resultlen;
	char err_buffer[MPI_MAX_ERROR_STRING];

    if (ierr != MPI_SUCCESS) {
       MPI_Error_class(ierr,&errclass);
       MPI_Error_string(ierr,err_buffer,&resultlen);
       fprintf(stderr, "Error class %d: %s", errclass, err_buffer);
       MPI_Finalize();             
    }
}

void main(int argc, char *args[]){
    int rank, n, f = 1, s, i, ierr;

    MPI_Init(&argc,&args);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &n);
    MPI_Errhandler_set(MCW,MPI_ERRORS_RETURN);

    for(i=1; i<=rank+1; i++)
        f *= i;

    ierr = MPI_Scan(&f, &s, 1, MPI_INT, MPI_SUM, MCW);
    error(ierr);

    if (rank==n-1)
        printf("Sum of factorial of all is %d\n", s);

    MPI_Finalize();
}