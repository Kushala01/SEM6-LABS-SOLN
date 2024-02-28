#include<stdio.h>
#include<stdlib.h>
#include<CL/cl.h>
#define max_src_size (0x100000)

int main(void){
	int n;
	printf("enterr the total number of elements");
	scanf("%d",&n);
	int *a = (int *)malloc(sizeof(int) * n);
	printf("enter the elements");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);

	//to lead cl file
	FILE *f;
	char * src;
	size_t src_n;
	f=fopen("prac.cl","r");
	if(!f){
		fprintf(stderr,"there is no file");
		getchar();
		exit(1);
	}src=(char*)malloc(max_src_size);
	src_n=fread(src,1,max_src_size,f);
	fclose(f);

	//get platform and device info
	cl_uint ret_plat_n;
	cl_platform_id plid=NULL;
	cl_device_id did=NULL;
	cl_uint ret_dev_n;
	int *c = (int *)malloc(sizeof(int) * n);
	cl_int ret=clGetPlatformIDs(1,&plid,&ret_plat_n);
	ret=clGetDeviceIDs(plid,CL_DEVICE_TYPE_GPU, 1, &did, &ret_dev_n);

	//execution environment context
	cl_context context=clCreateContext(NULL, 1, &did, NULL, NULL, &ret);

	//create command queue
	cl_command_queue cmdqueue=clCreateCommandQueueWithProperties(context, did, (cl_command_queue_properties)0,&ret);

	//create device buffers
	cl_mem a_mem_obj=clCreateBuffer(context, CL_MEM_READ_ONLY, n*sizeof(int), NULL, &ret);
	cl_mem c_mem_obj=clCreateBuffer(context, CL_MEM_READ_ONLY, n*sizeof(int), NULL, &ret);

	//write host data to device buffers
	ret =clEnqueueWriteBuffer(cmdqueue, a_mem_obj, CL_TRUE, 0, n*sizeof(int), a, 0, NULL, NULL);


	//create and complie the profram
	cl_program program=clCreateProgramWithSource(context, 1, (const char **)&src, (const size_t*)&src_n, &ret);

	ret=clBuildProgram(program, 1, &did, NULL,NULL,NULL);


	//create the kernel
	cl_kernel kernel=clCreateKernel(program, "octal", &ret);

	//set the kernel arguments
	ret=clSetKernelArg(kernel, 0, sizeof(cl_mem),(void*)&a_mem_obj);
	ret=clSetKernelArg(kernel, 1, sizeof(cl_mem),(void*)&c_mem_obj);


	//enqueue the kernel for exec
	size_t global_item_n=n;
	size_t local_item_n=1;
	ret=clEnqueueNDRangeKernel(cmdqueue, kernel, 1, NULL, &global_item_n, &local_item_n, 0, NULL, NULL);

	//read the output buffer back to the host
	ret=clEnqueueReadBuffer(cmdqueue, c_mem_obj, CL_TRUE, 0, n*sizeof(int), c, 0, NULL, NULL);

	//displaying the output
	for(int i=0;i<n;i++)
		printf("\n for %d octal is %d\n",a[i],c[i]);

	//clean up
	//ret=clFinish(cmdqueue);
	ret=clFlush(cmdqueue);
	ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(cmdqueue);
    ret = clReleaseContext(context);
    free(a);
    free(c);

    getchar();
    return 0;
}