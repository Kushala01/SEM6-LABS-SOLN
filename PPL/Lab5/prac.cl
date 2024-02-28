__kernel void octal(__global int *a, __global int *c){
	int i=get_global_id(0);
	int val=a[i];
	int p=1;
	int oct=0;
	while(val>0){
		oct+=(val%8)*p;
		p*=10;
		val/=8;
	}c[i] = oct;
}