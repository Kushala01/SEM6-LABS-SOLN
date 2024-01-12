#Q1. Write a program to find the area of rectangle. Take input from user.
l = int(input("Enter Length:"))
b = int(input("Enter Breadth:"))
print("The area of rectangle is", l*b, "sq units")

#Q2. Write a program to swap the values of two variables.
a = int(input("Enter First Number:"))
b = int(input("Enter Second Number:"))
a,b=b,a
print("The swapped values are:",a,b)

#Q3.Write a program to find whether a number is even or odd.
a = int(input("Enter Number:"))
if(a%2==0):
  print("Even")
else:
  print("Odd")

#Q4.Write a program to check the largest among the given three numbers. (note: use elif here)
a = int(input("Enter A:"))
b = int(input("Enter B:"))
c = int(input("Enter C:"))

if a > b and a > c:
    print("A is greater")
elif b > a and b > c:
    print("B is greater")
else:
    print("C is greater")

#Q5.Write a program to demonstrate List functions and operations.
my_list = [1, 2, 3, 4, 5]
print("Element at index 2:", my_list[2])
my_list[1] = 10
print("Modified list:", my_list)
my_list.append(6)
print("List after appending 6:", my_list)
removed_element = my_list.pop(3)
print("Removed element:", removed_element)
print("List after removal:", my_list)
sub_list = my_list[1:4]
print("Sliced list:", sub_list)
new_list = my_list + [7, 8, 9]
print("Concatenated list:", new_list)
print("Length of the list:", len(new_list))

#Q6.Consider the tuple(1,3,5,7,9,2,4,6,8,10). Write a program to print half its values in one line and the other half in the next line.
my_tuple = (1, 3, 5, 7, 9, 2, 4, 6, 8, 10)
midpoint = len(my_tuple) // 2
print("First half:", my_tuple[:midpoint])
print("Second half:", my_tuple[midpoint:])

#Q7.Consider the tuple (12, 7, 38, 56, 78 ). Write a program to print another tuple whose values are even number in the given tuple.
original_tuple = (12, 7, 38, 56, 78)
even_numbers_tuple = tuple(num for num in original_tuple if num % 2 == 0)
print("Tuple with even numbers:", even_numbers_tuple)

#Q8.Write a Python program to print negative Numbers in a List using for loop. Eg. [11, −21, 0, 45, 66, −93].
my_list = [11, -21, 0, 45, 66, -93]
print("Negative Numbers:")
for num in my_list:
    if num < 0:
        print(num)

#Q9.Write a Python program to count positive and negative numbers in a List.

my_list = [11, -21, 0, 45, 66, -93]
positive_count = 0
negative_count = 0
for num in my_list:
    if num > 0:
        positive_count += 1
    elif num < 0:
        negative_count += 1
print("Positive Numbers:", positive_count)
print("Negative Numbers:", negative_count)

#Q10.Write a Python program to remove all even elements from a list.

my_list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
my_list = [num for num in my_list if num % 2 != 0]
print("List after removing even elements:", my_list)
