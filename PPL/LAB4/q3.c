#include "mpi.h"
#include<stdio.h>
#define size 3
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
    int rank, n, i, j, ierr;
    int t, a[size][size], c = 0;
    int s;

    MPI_Init(&argc,&args);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &n);
    MPI_Errhandler_set(MCW,MPI_ERRORS_RETURN);

    if (rank==0){
        printf("Enter %d elements:\n", size*size);
        for(i=0; i<size; i++)
            for(j=0; j<size; j++)
                scanf("%d",&a[i][j]);
        printf("Enter element to be searched: ");
        scanf("%d", &t);
    }

    ierr = MPI_Bcast(&t, 1, MPI_INT, 0, MCW);
    error(ierr);
    ierr = MPI_Bcast(a, size*size, MPI_INT, 0, MCW);
    error(ierr);

    for(j=0; j<size; j++)
        if (a[rank][j]==t)
            c += 1;

    ierr = MPI_Reduce(&c, &s, 1, MPI_INT, MPI_SUM, 0, MCW);
    error(ierr);
    
    if (rank==0)
        printf("Frequency of %d is %d\n", t, s);

    MPI_Finalize();
}