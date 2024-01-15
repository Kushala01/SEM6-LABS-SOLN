import pandas as pd

# Reading CSV file with no header
df = pd.read_csv('xyz.csv', header=None)

# Displaying the first 5 records
print("First 5 records:")
print(df.head())

# Displaying the last 5 records
print("\nLast 5 records:")
print(df.tail())

# Assigning custom column names
df.columns = ['preg', 'glu', 'bp', 'sft', 'ins', 'bmi', 'dpf', 'age', 'class']
