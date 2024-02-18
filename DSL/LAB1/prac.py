my_list = [1, 2, 3, 4, 5, 6, 7, 8]

# Print the second element
print(my_list[1])

# Modify the first element
my_list[0] = 10
print(my_list)

# Append an element
my_list.append(9)

# Count the occurrences of an element (1 in this case)
count_of_1 = my_list.count(1)
print("Count of 1:", count_of_1)

# Delete an element by index
del my_list[2]
print(my_list)

# Remove an element by value if it exists
if 3 in my_list:
    my_list.remove(3)
else:
    print("3 is not in the list")

# Insert an element at a specific index
my_list.insert(3, "what")
print(my_list)

# Reverse the list
my_list.reverse()
print(my_list)

# Concatenate the list with another list
sub_list = my_list + [10, 11, 12]
print(sub_list)

# Slice the list to get a sublist
sub_list = my_list[2:]
print(sub_list)

#tuple with even numbers
my_tuple=(1,2,3,4,5,6,7,8,9)
new_tup=tuple(i for i in my_tuple if i %2==0)
print(new_tup)