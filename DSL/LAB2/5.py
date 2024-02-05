import pandas as pd

# a) Create two data frames
df1 = pd.DataFrame({'Name': ['Alice', 'Bob', 'Charlie', 'David']})
df2 = pd.DataFrame({
    'Maths': [90, 85, 92, 88],
    'Physics': [88, 90, 91, 87],
    'Chemistry': [85, 89, 90, 88],
    'Biology': [92, 87, 88, 91]
})

# Display df1 and df2
print("DataFrame df1:")
print(df1)

print("\nDataFrame df2:")
print(df2)

# b) Concatenate two data frames
df_new = pd.concat([df1, df2], axis=1)

# Insert a new column 'Total' and find the sum of all marks
df_new['Total'] = df_new[['Maths', 'Physics', 'Chemistry', 'Biology']].sum(axis=1)

# Display the concatenated data frame with the 'Total' column
print("\nConcatenated DataFrame df_new:")
print(df_new)
