#include <mpi.h>
#include <stdio.h>
#include <math.h>
 
int main(int argc, char** argv) {
    int x = 2;
    
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double P = pow(x, rank);

    printf("Process %d: %d to the power of %d is %f \n", rank, x, rank, P);

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}
