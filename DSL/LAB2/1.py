# Program to demonstrate while loop with else

# Initialize a counter
counter = 0

# Set the maximum number of iterations
max_iterations = 5

# While loop to perform an operation (e.g., printing) for a certain number of iterations
while counter < max_iterations:
    print(f'Iteration {counter + 1}')
    counter += 1
else:
    # This block is executed when the condition in the while loop becomes False
    print('End of loop - Condition is False')
