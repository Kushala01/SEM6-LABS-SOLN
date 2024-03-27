#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 1024

__global__ void repeatString(char *s, char *rs, int len) {
    int i = threadIdx.x;
    int x = len;
    int sum = 0;

    if (i < len) 
    {
        for(int j=0; j<i; j++,x--)
            sum += x;
        for(int j=0; j<len-i; j++)
            rs[sum++] = s[j];
    }
}

int main() {
    char a[N];

    printf("Enter a string: ");
    scanf("%s", a);

    int an = strlen(a);
    int x = an*(an+1)/2;

    char* da;
    char* dres;

    cudaMalloc((void**)&da, an * sizeof(char));
    cudaMalloc((void**)&dres, x * sizeof(char));

    cudaMemcpy(da, a, an * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemset(dres, 0, sizeof(int));
        
    repeatString<<<1, an>>>(da, dres, an);
    
    char rs[x];
    cudaMemcpy(rs, dres, sizeof(char) * x, cudaMemcpyDeviceToHost);
    rs[x]='\0';

    printf("Result: %s\n",rs);

    cudaFree(da);
    cudaFree(dres);

    return 0;
}





    

    
    
   

    
