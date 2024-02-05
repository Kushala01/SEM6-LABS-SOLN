# Program to print negative numbers in a list using while loop

# Sample list of numbers
numbers = [10, -5, 8, -3, -7, 12, -15, 20]

# Initialize a counter
index = 0

# Length of the list
length = len(numbers)

# While loop to iterate through the list and print negative numbers
while index < length:
    current_number = numbers[index]

    # Check if the number is negative
    if current_number < 0:
        print(current_number)

    # Move to the next index
    index += 1