import pandas as pd

# Create the DataFrame
data = {
    'rank1': [28, 34, 29, 42],
    'rank2': ['Kavitha', 'Sudha', 'Raju', 'Vignesh'],
    'rank3': [10, 20, 15, 30],
    'rank4': [5, 8, 12, 7],
    'Age': [28, 34, 29, 42],
    'Name': ['Kavitha', 'Sudha', 'Raju', 'Vignesh']
}

A = pd.DataFrame(data)

# Sort the DataFrame by the 'Age' column
A_sorted = A.sort_values(by='Age')

# Display the sorted DataFrame
print(A_sorted)
