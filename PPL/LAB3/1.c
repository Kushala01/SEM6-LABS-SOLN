#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MCW MPI_COMM_WORLD
#define ll long long

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &rank);
    MPI_Comm_size(MCW, &size);
    ll int fact;
    ll int i, n;
    ll int rec;
    ll int arr[100], facts[100];

    if (rank == 0) {
        n = size;
        printf("Enter the numbers: ");
        for (i = 0; i < n; ++i)
            scanf("%lld", &arr[i]);
    }
    MPI_Scatter(arr, 1, MPI_LONG_LONG, &rec, 1, MPI_LONG_LONG, 0, MCW);
    printf("Process [%d] received = %lld.\n", rank, rec);
    fact = 1;

    for (i = 2; i <= rec; ++i)
        fact *= i;
    MPI_Gather(&fact, 1, MPI_LONG_LONG, facts, 1, MPI_LONG_LONG, 0, MCW);

    if (rank == 0) {
        printf("Sum of factorials = ");
        ll int sum = 0;
        for (i = 0; i < n; ++i) {
            sum += facts[i];
            printf("%lld %s", facts[i], (i != n - 1) ? "+ " : " ");
        }printf(" = %lld\n", sum);
    }
    MPI_Finalize();
    return 0;
}