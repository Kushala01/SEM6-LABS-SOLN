// The method evaluates the integral of 4/(1+x*x) between 0 and 1. 
// The method is simple: the integral is approximated by a sum of n intervals; 
// the approximation to the integral in each interval is (1/n)*4/(1+x*x). 
// The master process (rank 0) asks the user for the number of intervals; 
// the master should then broadcast this number to all of the other processes. 
// Each process then adds up every n'th interval (x = rank/n, rank/n+size/n,...). 
// Finally, the sums computed by each process are added together using a reduction. 
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MCW MPI_COMM_WORLD

void error(int ierr){
	int errclass,resultlen;
	char err_buffer[MPI_MAX_ERROR_STRING];

    if (ierr != MPI_SUCCESS){
       MPI_Error_class(ierr,&errclass);
       MPI_Error_string(ierr,err_buffer,&resultlen);
       fprintf(stderr, "Error class %d: %s", errclass, err_buffer);
       MPI_Finalize();             
    }
}

int main(int argc, char *args[]){
    int n, rank, size, i, ierr;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;

    MPI_Init(&argc, &args);
    MPI_Comm_size(MCW, &size);
    MPI_Comm_rank(MCW, &rank);
    MPI_Errhandler_set(MCW,MPI_ERRORS_RETURN);

    if (rank == 0){
        printf("Enter the number of intervals: (0 quits) ");
        scanf("%d", &n);
    }
    ierr = MPI_Bcast(&n, 1, MPI_INT, 0, MCW);
    error(ierr);
    if (n == 0)
        exit(1);

    h = 1.0 / (double)n;
    sum = 0.0;
    for (i = rank + 1; i <= n; i += size){
        x = h * ((double)i - 0.5);
        sum += 4.0 / (1.0 + x * x);
    }
    mypi = h * sum;

    ierr = MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MCW);
    error(ierr);

    if (rank == 0)
        printf("pi is approximately %.16f, Error is %.16f\n",pi, fabs(pi - PI25DT));

    MPI_Finalize();
    return 0;
}