#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define max_src_size (0x100000)

int main(void)
{
    int i, n;
    char str[20000];
    int num;

    printf("Enter string: ");
    scanf("%s", str);
    n = strlen(str);
    printf("Enter number: ");
    scanf("%d", &num);

    // load kernel src code
    FILE *f;
    char *src;
    size_t src_n;
    f = fopen("q1.cl", "r");
    if (!f)
    {
        fprintf(stderr, "Failed to load kernel!\n");
        getchar();
        exit(1);
    }
    src = (char*)malloc(max_src_size);
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
    cl_command_queue cmdqueue = clCreateCommandQueue(context, did, CL_QUEUE_PROFILING_ENABLE, &ret);  //NOT WITH PROPERTIES -- REMEMBER!!!!
    // clCreateCommandQueue(context, did, NULL, &ret);

    // Create memory buffers on device for each vector
    cl_mem s_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(char), NULL, &ret);
    cl_mem t_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, num * n * sizeof(char), NULL, &ret);                                      // CHANGE
    
    // copy lists a and b to resp memory buffers
    ret = clEnqueueWriteBuffer(cmdqueue, s_mem_obj, CL_TRUE, 0, n * sizeof(char), str, 0, NULL, NULL);

    // create program from the kernel src
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&src, (const size_t *)&src_n, &ret);

    // build the program
    ret = clBuildProgram(program, 1, &did, NULL, NULL, NULL);

    // Create the OpenCL kernel object
    cl_kernel kernel = clCreateKernel(program, "replicate", &ret);

    // Set the args of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&s_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&t_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(int), (void *)&n);

    // execute the OpenCL kernel on the array
    size_t global_item_n = num*n;                                                                                                      // CHANGE
    size_t local_item_n = 1;

    // execute the kernel on the device
    cl_event event;
    ret = clEnqueueNDRangeKernel(cmdqueue, kernel, 1, NULL, &global_item_n, &local_item_n, 0, NULL, &event);
    ret = clFinish(cmdqueue);

    // read the result in memory buffer on the device to the local variable strres
    char *strres = (char*)malloc(sizeof(char)*n*num);                                                                                // CHANGE
    ret = clEnqueueReadBuffer(cmdqueue, t_mem_obj, CL_TRUE, 0, num * n * sizeof(char), strres, 0, NULL, NULL);                       // CHANGE

    printf("Done");
    // strres[n*num]='\0';                                                                                                            // CHANGE
    printf("\nresultant string: %s\n", strres);                                                                                // CHANGE

    // Clean UP
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(s_mem_obj);
    ret = clReleaseMemObject(t_mem_obj);
    ret = clReleaseCommandQueue(cmdqueue);
    ret = clReleaseContext(context);

    free(strres);
    return 0;
}

