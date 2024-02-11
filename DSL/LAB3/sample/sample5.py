import numpy as np
a = np.arange(10)**3
print(a[2:5])
print(a[0:6:2])

b = np.array([[0, 1, 2, 3], [10, 11, 12, 13], [20, 21, 22, 23], [30, 31, 32, 33], [40, 41, 42, 43]])
print(b[2, 3])
print(b[0:5, 1])
print(b[-1, :])

for row in b:
    print(row)

for element in b.flat:
    print(element)
