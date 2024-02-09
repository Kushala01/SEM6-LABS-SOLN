// vector-vector addition
#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#define max_src_size (0x100000)

int main(void){
    int i, n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements: ");
    int *a = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // load kernel src code
    FILE *f;
    char *src;
    size_t src_n;
    f = fopen("q3.cl", "r");
    if (!f){
        fprintf(stderr, "Failed to load kernel!\n");
        getchar();
        exit(1);
    }
    src = (char *)malloc(max_src_size);
    src_n = fread(src, 1, max_src_size, f);
    fclose(f);

    // get platform and device info
    cl_platform_id plid = NULL;
    cl_device_id did = NULL;
    cl_uint ret_dev_n;
    cl_uint ret_plat_n;

    cl_int ret = clGetPlatformIDs(1, &plid, &ret_plat_n);
    ret = clGetDeviceIDs(plid, CL_DEVICE_TYPE_GPU, 1, &did, &ret_dev_n);

    cl_context context = clCreateContext(NULL, 1, &did, NULL, NULL, &ret);
    cl_command_queue cmdqueue = clCreateCommandQueueWithProperties(context, did, (cl_command_queue_properties)0, &ret);
    
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, n * sizeof(int), NULL, &ret);  // CHNAGED TO READ_WRITE
    ret = clEnqueueWriteBuffer(cmdqueue, a_mem_obj, CL_TRUE, 0, n * sizeof(int), a, 0, NULL, NULL);
    
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&src, (const size_t *)&src_n, &ret);
    ret = clBuildProgram(program, 1, &did, NULL, NULL, NULL);

    cl_kernel kernel = clCreateKernel(program, "swap", &ret);
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);

    // execute the OpenCL kernel on the array
    size_t global_item_n = n/2;
    // size_t global_item_n = n;  // THEN IN CL FILE, JUST CHECK IF i%2==0 THEN SWAP
    size_t local_item_n = 1;

    // execute the kernel on the device
    cl_event event;
    ret = clEnqueueNDRangeKernel(cmdqueue, kernel, 1, NULL, &global_item_n, &local_item_n, 0, NULL, NULL);
    ret = clFinish(cmdqueue);
    ret = clEnqueueReadBuffer(cmdqueue, a_mem_obj, CL_TRUE, 0, n * sizeof(int), a, 0, NULL, NULL);  // ADD THIS!!!!!!!
    // Display the result to the screen
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    // Clean UP
    ret = clFlush(cmdqueue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseCommandQueue(cmdqueue);
    ret = clReleaseContext(context);

    free(a);
    getchar();
    return 0;
}