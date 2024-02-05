import pandas as pd

# a) Define a dictionary containing Students data {Name, Height, Qualification}
students_data = {
    'Name': ['Alice', 'Bob', 'Charlie', 'David'],
    'Height': [160, 175, 162, 168],
    'Qualification': ['Bachelor', 'Master', 'PhD', 'Bachelor']
}

# Convert the dictionary into DataFrame
df = pd.DataFrame(students_data)

# Display the DataFrame
print("Original DataFrame:")
print(df)

# b) Use DataFrame.insert() to add a new column 'Age'
age_list = [23, 28, 25, 22]
df.insert(loc=2, column='Age', value=age_list)

# Display the DataFrame after adding the 'Age' column
print("\nDataFrame after adding 'Age' column:")
print(df)
