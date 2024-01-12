#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int operation = rank % 4; // Each process handles a different operation

    int operand1 = 10; // Example operands
    int operand2 = 5;
    double result;

    switch (operation) {
        case 0: // Addition
            result = operand1 + operand2;
            printf("Process %d: Result of addition: %f\n", rank, result);
            break;

        case 1: // Subtraction
            result = operand1 - operand2;
            printf("Process %d: Result of subtraction: %f\n", rank, result);
            break;

        case 2: // Multiplication
            result = operand1 * operand2;
            printf("Process %d: Result of multiplication: %f\n", rank, result);
            break;

        case 3: // Division
            result = operand1 / (double)operand2;
            printf("Process %d: Result of division: %f\n", rank, result);
            break;

        default:
            break;
    }

    MPI_Finalize();
    return 0;
}
