__kernel void decimal(__global int *a, __global int *c){
    // Get the index of the current work item
    int i = get_global_id(0);
    // Do the operation - bin to decimal
    int val = a[i];
    int dec = 0;
    int p = 1;
    while (val>0){
        dec = dec + p*(val%10);
        p *= 2;
        val /= 10;
    }
    c[i] = dec;
}