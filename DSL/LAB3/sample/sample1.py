import numpy as np

# 1. Array creation
A = np.array([2, 5, 10])
print(A.dtype)  # int64

B = np.array([2.4, 10.6, 5.2])
print(B.dtype)  # float64

# Creating a 2-dimensional array
C = np.array([(3, 4, 5), (12, 6, 1)])

# Creating zero matrix of dimension 2x4
Z = np.zeros((2, 4))
print(Z)

# Creating ones matrix of dimension 3x3
O = np.ones((3, 3))
print(O)

# Creating a sequence of data using arange
S = np.arange(10, 30, 5)
print(S)  # [10 15 20 25]

# arange with float arguments
F = np.arange(0, 2, 0.3)
print(F)
# [0.  0.3 0.6 0.9 1.2 1.5 1.8]