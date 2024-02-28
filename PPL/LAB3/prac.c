#include<stdio.h>
#include<mpi.h>
#define MCW MPI_COMM_WORLD

int fact(int num){
	int val=1;
	for(int i=2;i<=num;i++){
		val=val*i;
	}
	return val;
}

int main(int argc, char ** argv){
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MCW,&rank);
	MPI_Comm_size(MCW,&size);
	int arr[size];
	int val;

	if(rank==0){
		printf("\nenter the elements in the array:\n");
		for(int i=0;i<size;i++)
			scanf("%d",&arr[i]);
	}
	MPI_Scatter(arr,1,MPI_INT,&val,1,MPI_INT,0,MCW);
	int ans=fact(val);
	MPI_Gather(&ans,1,MPI_INT,arr,1,MPI_INT,0,MCW);
	if(rank==0){
		printf("the sum is:\n");
		printf("%d ",arr[0]);
		int soln=arr[0];
		for(int i=1;i<size;i++){
			printf("+ %d ",arr[i]);
			soln+=arr[i];
		}printf("= %d",soln);
	}MPI_Finalize();
	return 0;
}