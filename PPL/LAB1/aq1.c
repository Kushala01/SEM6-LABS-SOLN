#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>
#define MCW MPI_COMM_WORLD

int main(int argc, char ** argv){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MCW,&rank);
    MPI_Comm_size(MCW,&size);
    int arr[]={18,523,301,1234,2,14,108,150,1928};
    int ans[9];

    for(int i = 0; i < 9; i++){
        int n = arr[i];
        int reversed = 0;
        while(n != 0){
            int digit = n % 10;
            reversed = reversed * 10 + digit;
            n /= 10;
        }
        ans[i] = reversed;
    }
    printf("\nAfter reversing in rank %d:\n", rank);
    for(int i = 0; i < 9; i++){
        printf("%d,\t", ans[i]);
    }
    printf("\n");
    MPI_Finalize();
    return 0;
}