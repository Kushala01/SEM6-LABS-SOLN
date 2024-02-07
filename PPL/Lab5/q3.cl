__kernel void swap(__global int *a){
    // Get the index of the current work item
    int i = get_global_id(0)*2;
    //int i = get_global_id(0);
    // Do the operation 
    int t = a[i];
    a[i] = a[i+1];
    a[i+1] = t;
}