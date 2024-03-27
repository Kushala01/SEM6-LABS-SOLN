__kernel void str_chgcase(__global char *a, __global char *b)
{
    int i = get_global_id(0);
    if(a[i]>='A' && a[i]<='Z')
        b[i] = a[i]+32;
    else
        b[i] = a[i]-32;
}