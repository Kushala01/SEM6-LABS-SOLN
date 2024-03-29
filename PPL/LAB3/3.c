#include <mpi.h>
#include <stdio.h>
#include <string.h>
#define MCW MPI_COMM_WORLD

int main(int argc, char* argv[]) {
    int rank, size;
    int count = 0;
    int b[100] = {0};

    int i, n, l;
    char str[100], c[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    if (rank == 0) {
        n = size;
        printf("Enter the string: ");
        scanf("%s", str);
        l = strlen(str) / n;
    }

    MPI_Bcast(&l, 1, MPI_INT, 0, MCW);
    MPI_Scatter(str, l, MPI_CHAR, c, l, MPI_CHAR, 0, MCW);
    count = 0;
    for (i = 0; i < l; ++i) {
        if (c[i] == 'a' || c[i] == 'e' || c[i] == 'i' || c[i] == 'o' || c[i] == 'u' ||
            c[i] == 'A' || c[i] == 'E' || c[i] == 'I' || c[i] == 'O' || c[i] == 'U') 
            continue;
        count += 1;
    }

    printf("Process %d Count = %d\n", rank, count);
    MPI_Gather(&count, 1, MPI_INT, b, 1, MPI_INT, 0, MCW);

    if (rank == 0) {
        int tcount = 0;
        for (i = 0; i < n; i++)
            tcount += b[i];
        printf("Total non-vowels = %d\n", tcount);
    } MPI_Finalize();
}