import numpy as np

# Mapping by Value
a = np.array([(3, 2, 9), (1, 6, 7)])
s1 = 0

for row in a:
    for col in row:
        s1 += col

print("Sum using value mapping:", s1)

# Mapping by Index
a = np.array([(3, 2, 9), (1, 6, 7)])
s = 0

for i in range(a.shape[0]):
    for j in range(a.shape[1]):
        s += a[i, j]

print("Sum using index mapping:", s)
