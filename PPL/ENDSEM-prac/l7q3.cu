#include<stdio.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>
#define n 10
#define m 5

__global__ void convolution(int *d_inp,int * d_out, int * d_mask){
	int tid=blockDim.x*blockIdx.x+threadIdx.x;
	int start= tid - m/2;
	int ans=0;
	for(int j=0;j<m;j++){
		if(start+j>=0 && start+j<=n){
			ans+=d_inp[start+j]*d_mask[j];
		}
	}d_out[tid]=ans;
}

int main(){
	int inp[n],out[n],mask[m];
	int *d_inp,*d_out, *d_mask;
	printf("\nenter %d digits for input array\n",n);
	for(int i=0;i<n;i++ ){
	scanf("%d",&inp[i]);
	}printf("\nenter %d digits for input array\n",m);
	for(int i=0;i<m;i++ ){
	scanf("%d",&mask[i]);
	}
	cudaMalloc((void**)&d_inp,n*sizeof(int));
	cudaMalloc((void**)&d_out,n*sizeof(int));
	cudaMalloc((void**)&d_mask,m*sizeof(int));

	cudaMemcpy(d_inp,inp,n*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(d_mask,mask,m*sizeof(int),cudaMemcpyHostToDevice);

	convolution<<<1,n>>>(d_inp,d_out,d_mask);

	cudaMemcpy(out,d_out,n*sizeof(int),cudaMemcpyDeviceToHost);

	printf("\n the resultant is \n");
	for(int i=0;i<n;i++)
		printf("%d\n",out[i]);

	cudaFree(d_out);
	cudaFree(d_inp);
	cudaFree(d_mask);
	return 0;
}