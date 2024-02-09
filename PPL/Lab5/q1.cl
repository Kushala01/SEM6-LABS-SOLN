__kernel void octal(__global int *a, __global int *c){
    // Get the index of the current work item
    int i = get_global_id(0);
    // Do the operation
    int val = a[i];
    int oct = 0;
    int p = 1;
    while(val>0){
        oct += (val%8)*p;
        p = p*10;
        val /= 8;
    }c[i] = oct;
}