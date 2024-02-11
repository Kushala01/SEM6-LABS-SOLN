import numpy as np

a = np.array([20, 30, 40, 50])
b = np.arange(4)
c = a - b
print("a - b:", c)
print("b^2:", b**2)
print("10 * sin(a):", 10 * np.sin(a))
print("a < 35:", a < 35)

A = np.array([[1, 1], [0, 1]])
B = np.array([[2, 0], [3, 4]])
print("A * B (Elementwise product):", A * B)
print("np.dot(A, B) (Matrix product):", np.dot(A, B))

b = np.arange(12).reshape(3, 4)
print("Sum of each column:", b.sum(axis=0))
print("Sum of each row:", b.sum(axis=1))

print("Flattened array:", b.ravel())
B1 = b.reshape(2, 6)
print("Reshaped matrix (4x5):", B1)