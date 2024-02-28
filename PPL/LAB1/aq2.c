#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>
#define MCW MPI_COMM_WORLD

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);

    if (size != 2) {
        printf("This program requires exactly 2 processes.\n");
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    int lower_bound, upper_bound;
    if (rank == 0) {
        lower_bound = 1;
        upper_bound = 50;
    } else {
        lower_bound = 51;
        upper_bound = 100;
    }

    printf("Process %d checking prime numbers between %d and %d\n", rank, lower_bound, upper_bound);

    for (int num = lower_bound; num <= upper_bound; num++) {
        if (isPrime(num)) {
            printf("%d is prime.\n", num);
        }
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}