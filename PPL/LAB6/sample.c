#include <stdio.h>
#include <CL/cl.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define max_src_size (0x100000)

int main(void)
{
    int i, n;
    time_t start, end;
    start = clock();
    char tempstr[20486];

    for(i=0;i<20485;i++)
        tempstr[i]='A';
    tempstr[20485]='\0';

    n = strlen(tempstr);
    n++;
    char *str = (char*)malloc(sizeof(char)*n);
    strcpy(str, tempstr);

    // load kernel src code
    FILE *f;
    char *src;
    size_t src_n;
    f = fopen("strtoggle.cl", "r");

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
    cl_mem t_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, n * sizeof(char), NULL, &ret);
    
    // copy lists a and b to resp memory buffers
    ret = clEnqueueWriteBuffer(cmdqueue, s_mem_obj, CL_TRUE, 0, n * sizeof(char), str, 0, NULL, NULL);

    // create program from the kernel src
    cl_program program = clCreateProgramWithSource(context, 1, (const char **)&src, (const size_t *)&src_n, &ret);

    // build the program
    ret = clBuildProgram(program, 1, &did, NULL, NULL, NULL);

    // Create the OpenCL kernel object
    cl_kernel kernel = clCreateKernel(program, "str_chgcase", &ret);

    // Set the args of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&s_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&t_mem_obj);

    // execute the OpenCL kernel on the array
    size_t global_item_n = n;
    size_t local_item_n = 1;

    // execute the kernel on the device
    cl_event event;
    ret = clEnqueueNDRangeKernel(cmdqueue, kernel, 1, NULL, &global_item_n, &local_item_n, 0, NULL, &event);
    time_t stime = clock();
    ret = clFinish(cmdqueue);

    cl_ulong startt, endt;
    double tott;

    // Find the kernel execution start time
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(startt), &startt, NULL);
    clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(endt), &endt, NULL);
    tott = (double)(endt-startt);

    // read the result in memory buffer on the device to the local variable strres
    char *strres = (char*)malloc(sizeof(char)*n);
    ret = clEnqueueReadBuffer(cmdqueue, t_mem_obj, CL_TRUE, 0, n * sizeof(char), strres, 0, NULL, NULL);

    printf("\nDone");
    strres[n-1]='\0';
    printf("\nresultant toggled string: %s", strres);

    // Clean UP
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(s_mem_obj);
    ret = clReleaseMemObject(t_mem_obj);
    ret = clReleaseCommandQueue(cmdqueue);
    ret = clReleaseContext(context);

    end = clock();
    printf("\n\nTime taken to execute the KERNEL in milliseconds = %0.3f msec\n\n", tott/1000000);
    printf("\n\nTime taken to execute the whole program in seconds = %0.3f sec\n\n", (end-start)/(double)CLOCKS_PER_SEC);


    free(str);
    free(strres);
    return 0;
}
