#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv []) {
    int rank, size;
    char b[200], str1[100], str2[100], c1[100], c2[100], concatted[200];
    int i, m;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0) { 
        printf("Enter string 1: ");
        scanf("%s", str1);
        printf("Enter string 2: ");
        scanf("%s", str2);
        m = strlen(str1) / size;
    }
    
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(str1, m, MPI_CHAR, c1, m, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(str2, m, MPI_CHAR, c2, m, MPI_CHAR, 0, MPI_COMM_WORLD);
    
    for (i = 0; i < m; i++) {
        concatted[2 * i] = c1[i];
        concatted[2 * i + 1] = c2[i];   
    }
    MPI_Gather(concatted, 2*m, MPI_CHAR, b, 2*m, MPI_CHAR, 0, MPI_COMM_WORLD);
    
    if (rank == 0)
        printf("Concatted: %s\n", b);

    MPI_Finalize();
}