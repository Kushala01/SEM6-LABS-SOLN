import pandas as pd
import numpy as np

# Creating a DataFrame with random data
dates = pd.date_range('20130101', periods=100)
df = pd.DataFrame(np.random.randn(100, 4), index=dates, columns=list('ABCD'))

# Viewing the first 5 records
print("First 5 records:")
print(df.head())

# Viewing the last 5 records
print("\nLast 5 records:")
print(df.tail())

# Viewing the index
print("\nIndex:")
print(df.index)

# Viewing the column names
print("\nColumn names:")
print(df.columns)

# Transposing the DataFrame
print("\nTransposed DataFrame:")
print(df.T)

# Sorting by axis (columns in this case) in descending order
print("\nSorting by Axis:")
print(df.sort_index(axis=1, ascending=False))

# Sorting by values in column 'B'
print("\nSorting by Values in Column 'B':")
print(df.sort_values(by='B'))

# Slicing the first 3 records (rows)
print("\nSlicing the first 3 records:")
print(df[0:3])

# Slicing with index name for a specific date range
print("\nSlicing with index name for a date range:")
print(df['20130105':'20130110'])

# Slicing with row and column index
print("\nSlicing with row and column index:")
# Fetching entire 1st row
print(df.iloc[0])
# Fetching 1st row, first 2 columns
print(df.iloc[0, :2])
# Fetching a single element (1st row, 1st column)
print(df.iloc[0, 0])

# Selecting a single column ('A'), which yields a Series
print("\nSelecting a single column ('A'):")
print(df['A'])

# Selecting more than one column ('A' and 'B'), entire 2 columns
print("\nSelecting more than one column ('A' and 'B'):")
print(df[['A', 'B']])

# Selecting more than one column ('A' and 'B') with the first 5 records
print("\nSelecting more than one column with the first 5 records:")
print(df[['A', 'B']][:5])
# Alternatively using loc for a specific date range and selected columns
print(df.loc['20130101':'20130105', ['A', 'B']][:5])