import numpy as np
a = np.arange(15).reshape(3, 5)
print(a)
print(a.shape)  # (3, 5)
print(a.size)   # 15
print(a.T)      # Transpose to a 5x3 matrix

c = np.arange(24).reshape(2, 3, 4)
print(c)
print(c.shape)  # (2, 3, 4)
print(c[1, ...])  # Equivalent to c[1, :, :]
print(c[..., 2])  # Equivalent to c[:, :, 2]