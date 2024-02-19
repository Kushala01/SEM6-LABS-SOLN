'''Operations on Arrays (use numpy wherever required):
a) Create array from list with type float
b) Create array from tuple
c) Creating a 3X4 array with all zeros
d) Create a sequence of integers from 0 to 20 with steps of 5
e) Reshape 3X4 array to 2X2X3 array
f) Find maximum and minimum element of array, Row wise max and min, column wise max
and min and sum of elements. (Use functions max(), min(), sum())'''
import numpy as np
x=[float(i) for i in input().split()]
Arr=np.array(x)
y=tuple([float(i) for i in input().split()])
Arr_tup=np.array(y)
arr_zeros=np.zeros((3,4))
print(arr_zeros)
arr_seq=np.arange(0,21,5)
arr_zeros.reshape((2,2,3))
my_arr=np.array([1,2,3],[4,5,6],[7,8,9])
print(np.max(my_arr,axis=0),np.max(my_arr,axis=1),np.min(my_arr,axis=0),np.min(my_arr,axis=1),np.sum(my_arr,axis=0),np.sum(my_arr,axis=1))