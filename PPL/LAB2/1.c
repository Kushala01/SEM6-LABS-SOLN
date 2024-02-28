#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <ctype.h>
#define MAX_STRING_SIZE 100

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank, size, len;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char str[MAX_STRING_SIZE];

    if (rank == 0) {
        printf("Enter a string:\n");
        fgets(str, MAX_STRING_SIZE, stdin);
        len = strlen(str);
        MPI_Ssend(&len, 1, MPI_INT, 1, 100, MPI_COMM_WORLD);
        MPI_Ssend(str, len, MPI_CHAR, 1, 101, MPI_COMM_WORLD);
        printf("procces:0 sent string: %s\n", str);

        MPI_Recv(&len, 1, MPI_INT, 1, 102, MPI_COMM_WORLD, &status);
        MPI_Recv(str, len, MPI_CHAR, 1, 103, MPI_COMM_WORLD, &status);
        printf("Received string: %s\n", str);
    } else if (rank == 1) {
        MPI_Recv(&len, 1, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        MPI_Recv(str, len, MPI_CHAR, 0, 101, MPI_COMM_WORLD, &status);
        printf("Received string: %s\n", str);

        for (int i = 0; i < len; i++) {
            if (islower(str[i]))
                str[i] = toupper(str[i]);
            else if (isupper(str[i]))
                str[i] = tolower(str[i]);
        }
        MPI_Ssend(&len, 1, MPI_INT, 0, 102, MPI_COMM_WORLD);
        MPI_Ssend(str, len, MPI_CHAR, 0, 103, MPI_COMM_WORLD);
        printf("procces:1 sent string: %s\n", str);
    }
    MPI_Finalize();
    return 0;
}