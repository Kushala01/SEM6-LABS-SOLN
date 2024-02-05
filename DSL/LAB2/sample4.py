import pandas as pd
import numpy as np

# Creating a DataFrame with random data
dates = pd.date_range('20130101', periods=10)
df = pd.DataFrame(np.random.randn(10, 4), index=dates, columns=list('ABCD'))

# Boolean Indexing: Fetching all rows where column 'A' has positive values
print("Boolean Indexing:")
print(df[df['A'] > 0])

# Adding a new column 'F' with categorical character data
df['F'] = ['Male', 'Female', 'Female', 'Male', 'Female', 'Female', 'Male', 'Male', 'Female', 'Male']

# Setting by assigning with a numpy array: Replacing the 'D' column with all 5
df.loc[:, 'D'] = np.array([5] * len(df))
print("\nSetting 'D' column with all 5:")
print(df)

# Deleting a column: Dropping the 'C' column
df.drop('C', axis=1, inplace=True)
print("\nAfter dropping 'C' column:")
print(df)

# Deleting a row: Dropping the row with index 20130104
df.drop(pd.Timestamp('20130104'), axis=0, inplace=True)
print("\nAfter dropping row with index 20130104:")
print(df)

# Concatenating two DataFrames horizontally
df1 = pd.DataFrame(np.random.randn(10, 5), columns=list('ABCDE'))
df2 = pd.DataFrame(np.random.randn(10, 3), columns=list('FGH'))

df_new = pd.concat([df1, df2], axis=1)
print("\nConcatenation horizontally:")
print(df_new)
print("Shape after concatenation:", df_new.shape)

# Concatenating two DataFrames vertically
A = pd.DataFrame(np.random.randn(10, 5), columns=list('ABCDE'))
B = pd.DataFrame(np.random.randn(15, 5), columns=list('ABCDE'))

D = pd.concat([A, B], axis=0)
print("\nConcatenation vertically:")
print(D)
print("Shape after concatenation:", D.shape)
