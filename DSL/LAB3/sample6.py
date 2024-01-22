import numpy as np

# Array Operations
a = np.array([20, 30, 40, 50])
b = np.arange(4)
c = a - b
print("a - b:", c)
print("b^2:", b**2)
print("10 * sin(a):", 10 * np.sin(a))
print("a < 35:", a < 35)

# Matrix Operations
A = np.array([[1, 1], [0, 1]])
B = np.array([[2, 0], [3, 4]])
print("A * B (Elementwise product):", A * B)
print("np.dot(A, B) (Matrix product):", np.dot(A, B))

# Another Matrix Sum Operations
b = np.arange(12).reshape(3, 4)
print("Sum of each column:", b.sum(axis=0))
print("Sum of each row:", b.sum(axis=1))

# Changing the Shape of a Matrix
print("Flattened array:", b.ravel())
try:
    B1 = b.reshape(4, 5)  # Raises ValueError
except ValueError as e:
    print("Error:", e)

# Stacking Operations
A1 = np.array([(3, 4, 5), (12, 6, 1)])
A2 = np.array([(1, 2, 6), (-4, 3, 8)])
D1 = np.vstack((A1, A2))
print("Vertical Stack D1:\n", D1)

D2 = np.hstack((A1, A2))
print("Horizontal Stack D2:\n", D2)

a = np.array([4., 2.])
b = np.array([3., 8.])
result_column_stack = np.column_stack((a, b))
print("Column-wise Stack:\n", result_column_stack)

# Indexing with Array of Indices
a = np.arange(12)**2
i = np.array([1, 1, 3, 8, 5])
result_i = a[i]
print("Indexing with array i:", result_i)

j = np.array([[3, 4], [9, 7]])
result_j = a[j]
print("Indexing with array j:\n", result_j)