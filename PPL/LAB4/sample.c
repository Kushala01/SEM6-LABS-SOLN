#include "mpi.h"
#include<stdio.h>

void main(int argc, char *args[])
{
    int rank, n, f = 1, s, i;

    MPI_Init(&argc,&args);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n);

    for(i=1; i<=rank+1; i++)
        f *= i;
 
    MPI_Reduce(&f, &s, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank==0)
        printf("Sum of factorial of all is %d\n", s);

    MPI_Finalize();
}
