import pandas as pd
import numpy as np
from IPython.display import display

# Create DataFrame df1
df1 = pd.DataFrame({
    'A': pd.Timestamp('20130102'),
    'B': np.array([3] * 4, dtype='int32'),
    'C': pd.Categorical(['Male', 'Female', 'Male', 'Female'])
})

# Display df1
display(df1)

# Display dtypes of df1
print("Data Types:")
print(df1.dtypes)

# Display the first few rows of df1
print("\nHead:")
print(df1.head())

# Display the last few rows of df1
print("\nTail:")
print(df1.tail())

# Display summary statistics of df1
print("\nSummary:")
print(df1.describe())

# Transpose df1 and display
print("\nTranspose:")
print(df1.T)
