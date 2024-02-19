'''Operations on Arrays (use numpy wherever required):
a) Create array from list with type float
b) Create array from tuple
c) Creating a 3X4 array with all zeros
d) Create a sequence of integers from 0 to 20 with steps of 5
e) Reshape 3X4 array to 2X2X3 array
f) Find maximum and minimum element of array, Row wise max and min, column wise max
and min and sum of elements. (Use functions max(), min(), sum())'''
import numpy as np
# Create array from list with type float
x = [float(i) for i in input().split()]
arr_list = np.array(x)

# Create array from tuple
y = tuple([float(i) for i in input().split()])
arr_tuple = np.array(y)

# Creating a 3X4 array with all zeros
arr_zeros = np.zeros((3, 4))
print(arr_zeros)

# Create a sequence of integers from 0 to 20 with steps of 5
arr_seq = np.arange(0, 21, 5)
print(arr_seq)

# Reshape 3X4 array to 2X2X3 array
arr_reshaped = arr_zeros.reshape((2, 2, 3))
print(arr_reshaped)

# Create a 3X3 array using a list of lists
my_arr = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])

# Find maximum and minimum element of array, row-wise max and min, column-wise max
# and min, and sum of elements
print("Maximum element:", np.max(my_arr))
print("Minimum element:", np.min(my_arr))
print("Row-wise maximum:", np.max(my_arr, axis=1))
print("Row-wise minimum:", np.min(my_arr, axis=1))
print("Column-wise maximum:", np.max(my_arr, axis=0))
print("Column-wise minimum:", np.min(my_arr, axis=0))
print("Sum of elements:", np.sum(my_arr))