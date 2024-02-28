#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

int reverseDigits(int num) {
    int reversed = 0;
    while (num != 0) {
        int digit = num % 10;
        reversed = reversed * 10 + digit;
        num /= 10;
    }
    return reversed;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    int arr[] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *localArray = (int *)malloc(n / size * sizeof(int));
    MPI_Scatter(arr, n / size, MPI_INT, localArray, n / size, MPI_INT, 0, MCW);

    for (int i = 0; i < n / size; i++) {
        localArray[i] = reverseDigits(localArray[i]);
    }

    // Gather results to one process if needed
    if (rank == 0) {
        int *resultArray = (int *)malloc(n * sizeof(int));
        MPI_Gather(localArray, n / size, MPI_INT, resultArray, n / size, MPI_INT, 0, MCW);

        printf("Reversed array:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", resultArray[i]);
        }
        printf("\n");

        free(resultArray);
    } else {
        MPI_Gather(localArray, n / size, MPI_INT, NULL, 0, MPI_INT, 0, MCW);
    }

    free(localArray);
    MPI_Finalize();
    return 0;
}