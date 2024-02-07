__kernel void comp(__global int *a, __global int *c){
    // Get the index of the current work item
    int i = get_global_id(0);
    // Do the operation
    c[i] = ~a[i];
}