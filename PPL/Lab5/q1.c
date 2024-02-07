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
    f = fopen("q1.cl", "r");
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

    // Create OpenCL context
    cl_context context = clCreateContext(NULL, 1, &did, NULL, NULL, &ret);

    // Create command queue
    cl_command_queue cmdqueue = clCreateCommandQueueWithProperties(context, did, (cl_command_queue_properties)0, &ret);
    // clCreateCommandQueue(context, did, NULL, &ret);

    // Create memory buffers on device for each vector
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &ret);

    // copy lists a to resp memory buffer
    ret = clEnqueueWriteBuffer(cmdqueue, a_mem_obj, CL_TRUE, 0, n * sizeof(int), a, 0, NULL, NULL);

    // create program from the kernel src
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&src, (const size_t *)&src_n, &ret);

    // build the program
    ret = clBuildProgram(program, 1, &did, NULL, NULL, NULL);

    // Create the OpenCL kernel object
    cl_kernel kernel = clCreateKernel(program, "octal", &ret);

    // Set the args of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&c_mem_obj);

    // execute the OpenCL kernel on the array
    size_t global_item_n = n;
    size_t local_item_n = 1;

    // execute the kernel on the device
    cl_event event;
    ret = clEnqueueNDRangeKernel(cmdqueue, kernel, 1, NULL, &global_item_n, &local_item_n, 0, NULL, NULL);
    ret = clFinish(cmdqueue);

    int *c = (int *)malloc(sizeof(int) * n);
    ret = clEnqueueReadBuffer(cmdqueue, c_mem_obj, CL_TRUE, 0, n * sizeof(int), c, 0, NULL, NULL);

    // Display the result to the screen
    for (i = 0; i < n; i++)
        printf("Octal of %d is %d\n", a[i], c[i]);
    // Clean UP
    ret = clFlush(cmdqueue);
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
