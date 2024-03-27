__kernel void replicate(__global char *a, __global char *b, int n)
{
    int i = get_global_id(0);
    for(int k = 0; k<n; k++)
        b[i*n + k] = a[k];
}