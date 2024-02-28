#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

int main(int argc, char** argv) {
    int rank, size, i;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    int n;
    char word[100];

    if (rank == 0) {
        printf("Enter a word of length %d: ", size);
        scanf("%s", word);
        n = strlen(word);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MCW);
    MPI_Bcast(word, n, MPI_CHAR, 0, MCW);

    char output[100];
    int offset = 0;

    for (i = 0; i < n; i++) {
        int repeat = i + 1;
        for (int j = 0; j < repeat; j++) {
            output[offset++] = word[i];
        }
    }

    // Adjust the loop to repeat based on the rank
    for (i = 0; i < rank + 1; i++) {
        MPI_Send(output, offset, MPI_CHAR, 0, 0, MCW);
    }

    if (rank == 0) {
        for (i = 0; i < size; i++) {
            MPI_Recv(output, offset, MPI_CHAR, i, 0, MCW, MPI_STATUS_IGNORE);
            printf("Process %d: Input: %s, Output: %s\n", i, word, output);
        }
    }

    MPI_Finalize();
    return 0;
}