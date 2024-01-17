#include <mpi.h>
#include <stdio.h>

#define MAX_M 100
#define MAX_N 100

int main(int argc, char *argv[]) 
{
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n, M;
    int sendBuf[MAX_M * MAX_N];
    int recvBuf[MAX_M];
    double averages[MAX_N];

    if (rank == 0){
        printf("Enter the value of M: ");
        scanf("%d", &M);
        n=size;
        printf("Enter %d elements: ", M * n);
        for (int i = 0; i < M * n; ++i) 
            scanf("%d", &sendBuf[i]);
    } 

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD); 
    MPI_Scatter(sendBuf, M, MPI_INT, recvBuf, M, MPI_INT, 0, MPI_COMM_WORLD);

    double average = 0.0;
    for (int i = 0; i < M; ++i) 
        average += recvBuf[i];
    average /= M;

    MPI_Gather(&average, 1, MPI_DOUBLE, averages, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double totalAverage = 0.0;
        for (int i = 0; i < n; ++i) 
            totalAverage += averages[i];
        totalAverage /= n;
        printf("Total average = %lf\n", totalAverage);
    }
    MPI_Finalize();
    return 0;
}