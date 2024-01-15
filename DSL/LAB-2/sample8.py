import pandas as pd

# Reading CSV file with no header
W = pd.read_csv('xyz.xls', header=None)

# Displaying the first 5 records
print("CSV File (xyz.xls):")
print(W.head())

# Reading Excel file with sheet name specified
G = pd.read_excel('xyz.xlsx', sheet_name='Sheet1')

# Displaying the first 5 records
print("\nExcel File (xyz.xlsx):")
print(G.head())
