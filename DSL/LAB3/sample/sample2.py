import numpy as np
import random

# Using linspace to specify the total number of elements in the array
S1 = np.linspace(0, 2, 9)
print(S1)
# [0.   0.25 0.5  0.75 1.   1.25 1.5  1.75 2.  ]

# Random number generation using random module
print(random.choice([1, 2, 3, 4, 5]))  # Pick one number randomly from the list
print(random.choice('python'))  # Pick one character randomly from the string

# Pick one integer between 25 to 50
print(random.randrange(25, 50))

# Pick one integer between 25 to 50 with a step size of 2
print(random.randrange(25, 50, 2))

# Pick a random number between 0 to 1
print(random.random())

# Pick a floating-point number between 5 to 10
print(random.uniform(5, 10))

# Shuffle the elements of the list
my_list = [1, 2, 3, 4, 5]
random.shuffle(my_list)
print(my_list)

# Set the seed to get the same random value during every execution
random.seed(10)
print(random.random())