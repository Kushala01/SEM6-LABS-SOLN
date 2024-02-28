#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define MCW MPI_COMM_WORLD

// Function to check if a number is prime
int isPrime(int n) {
    if (n <= 1) return 0; // 0 and 1 are not prime
    if (n <= 3) return 1; // 2 and 3 are prime
    if (n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and 3 are not prime

    // Check all numbers of the form 6k +/- 1, up to sqrt(n)
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }

    return 1; // n is prime
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank, size, N;

    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    if (rank == 0) {
        printf("Enter the number of elements: ");
        scanf("%d", &N);

        int *array = (int *)malloc(N * sizeof(int));
        printf("Enter %d elements: ", N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &array[i]);
        }

        // Send the array size to all processes
        for (int i = 1; i < size; i++) {
            MPI_Send(&N, 1, MPI_INT, i, 0, MCW);
        }

        // Send array elements to each process
        for (int i = 1; i < size; i++) {
            MPI_Send(&array[i - 1], 1, MPI_INT, i, 0, MCW);
        }

        free(array);
    } else {
        // Receive the array size from rank 0
        MPI_Recv(&N, 1, MPI_INT, 0, 0, MCW, MPI_STATUS_IGNORE);
        int num;
        // Receive array elements from rank 0 and check if prime
        for (int i = 0; i < N; i++) {
            MPI_Recv(&num, 1, MPI_INT, 0, 0, MCW, MPI_STATUS_IGNORE);
            int is_prime = isPrime(num);
            // Send the result back to the master process
            MPI_Send(&is_prime, 1, MPI_INT, 0, i, MCW);
        }
    }

    if (rank == 0) {
        printf("Prime check results:\n");
        for (int i = 0; i < N; i++) {
            int result;
            MPI_Recv(&result, 1, MPI_INT, MPI_ANY_SOURCE, i, MCW, MPI_STATUS_IGNORE);
            printf("Element %d: %s\n", i + 1, result ? "Prime" : "Not prime");
        }
    }

    MPI_Finalize();
    return 0;
}