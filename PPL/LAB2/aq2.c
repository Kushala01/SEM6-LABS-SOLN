#include <stdio.h>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

// Function to calculate factorial
int factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank, size, N, sum = 0, local_sum = 0;
    int array[100]; // Maximum size for the array

    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    if (rank == 0) {
        printf("Enter the number of elements: ");
        scanf("%d", &N);

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
            MPI_Send(array, N, MPI_INT, i, 0, MCW);
        }
    } else {
        // Receive the array size from rank 0
        MPI_Recv(&N, 1, MPI_INT, 0, 0, MCW, MPI_STATUS_IGNORE);

        // Receive array elements from rank 0
        MPI_Recv(array, N, MPI_INT, 0, 0, MCW, MPI_STATUS_IGNORE);

        for (int i = 0; i < N; i++) {
            int factorial_val = factorial(array[i]);
            local_sum += factorial_val;

            for (int j = 1; j <= array[i]; j++) {
                local_sum += j;
            }
        }

        // Send the local sum to the root process
        MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MCW);
    }

    if (rank == 0) {
        for (int i = 0; i < size - 1; i++) {
            // Receive the local sums from all other processes
            MPI_Recv(&local_sum, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, MPI_STATUS_IGNORE);
            sum += local_sum;
        }
        
        printf("Result: %d\n", sum);
    }

    MPI_Finalize();
    return 0;
}