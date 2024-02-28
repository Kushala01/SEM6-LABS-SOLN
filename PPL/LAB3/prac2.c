#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define MAX_M 100
#define MAX_N 100

int findAvg(int arr[],int n){
	int soln=0;
	for(int i=0;i<n;i++){
		soln+=arr[i];
	}soln=soln/n;
	return soln;
}

int main(int argc,char**argv){
	int rank,size,m;
	int arr[MAX_M*MAX_N];
	int ans[MAX_M];
    int avgs[MAX_N];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0){
		printf("\nenter m:\n");
		scanf("%d",&m);
		printf("enter %d elements:",size*m);
		for(int i=0;i<size*m;i++){
			scanf("%d",&arr[i]);
		}
	}MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(arr,m,MPI_INT,ans,m,MPI_INT,0,MPI_COMM_WORLD);
	int soln=findAvg(ans,m);
	MPI_Gather(&soln,1,MPI_INT,avgs,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0){
		int final=findAvg(avgs,size);
		printf("%d",final);
	}MPI_Finalize();
	return 0;
}