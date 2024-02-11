import pandas as pd
import matplotlib.pyplot as plt

# Reading CSV file with no header and assigning column names
df = pd.read_csv('xyz.csv', header=None)
df.columns = ['preg', 'glu', 'bp', 'sft', 'ins', 'bmi', 'dpf', 'age', 'class']

# Displaying the first 5 records
print("First 5 records:")
print(df.head())

# Displaying the last 5 records
print("\nLast 5 records:")
print(df.tail())

# Scatter plot of 'bmi' against 'glu'
plt.scatter(df['bmi'], df['glu'])
plt.xlabel('BMI')
plt.ylabel('Glucose')
plt.title('Scatter Plot: BMI vs Glucose')
plt.show()

# Histogram for the 'age' column
df['age'].hist()
plt.xlabel('Age')
plt.ylabel('Frequency')
plt.title('Histogram: Age Distribution')
plt.show()
