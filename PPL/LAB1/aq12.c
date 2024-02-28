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
    int localArray[9];

    // Determine the chunk size
    int chunkSize = n / size;
    // Determine the starting index for the current process
    int startIndex = rank * chunkSize;
    // Determine the ending index for the current process
    int endIndex = (rank == size - 1) ? n : (rank + 1) * chunkSize;

    // Reverse the digits of the numbers assigned to the current process
    for (int i = startIndex; i < endIndex; i++) {
        localArray[i] = reverseDigits(arr[i]);
    }

    // Print the reversed array from each process
    printf("Reversed array in process %d:\n", rank);
    for (int i = startIndex; i < endIndex; i++) {
        printf("%d ", localArray[i]);
    }
    printf("\n");
    MPI_Finalize();
    return 0;
}