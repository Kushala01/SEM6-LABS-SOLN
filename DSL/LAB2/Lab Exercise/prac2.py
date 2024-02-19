import pandas as pd
import numpy as np
from IPython.display import display
import matplotlib.pyplot as plt

# Load data from a CSV file into a DataFrame
data = pd.read_csv("ans.csv", sep='\t')

# Print the first few rows of the DataFrame
print(data.head())

# Print the last two rows of the DataFrame
print(data.tail(2))

# Print statistical summary of the DataFrame
print('Describe: \n\n\n\n\n\n', data.describe())

# Transpose the DataFrame (swap rows and columns)
print(data.T)

# Filter rows where the 'name' column equals 'batman'
filteredRow = data[data['name'] == 'batman']
print(filteredRow)

# Replace occurrences of 'batman' with 'spyderman' in the DataFrame
replaced_row = data.replace('batman', 'spyderman')
print(replaced_row)

# Remove the 'name' column from the DataFrame
remove_col = data.drop('name', axis=1)
#data.drop('name',axis=1,inplace='True')
print(remove_col)

# Print the original DataFrame to show it's unchanged
print(data)

# Remove the row at index 1 from the DataFrame
remove_row = data.iloc[1:2]
print(remove_row)

# Check the type of the DataFrame
print(type(data))

# Define a new row of data
new_row = {'name': ['kushu','biyc'], 'hieght': [121,13], 'weight': [33,44], 'bmi': [12,33]}

# Append the new row to the DataFrame
new_row_added = pd.concat([data, pd.DataFrame(new_row)], ignore_index=True)
print(new_row_added)

# Drop duplicate rows based on the 'name' column
new_data = data.drop_duplicates(subset='name')

# Create a new DataFrame with custom index labels
df = pd.DataFrame(data, index=['rank1', 'rank2', 'rank3'])
print(df)
# Display the DataFrame with custom index labels
display(df)

# Sort the DataFrame by columns in descending order
data.sort_index(axis=1, ascending=False)
print(data)

# Sort the DataFrame by values in the 'name' column
data.sort_values(by='name')
print(data)

# Fetch the entire 1st row of the DataFrame
data.iloc[0]

# Fetch the 1st row and the first 2 columns of the DataFrame
data.iloc[0, :2]
print(data.iloc[0, 0])

# Select the 'name' column of the DataFrame
print(data['name'])

# Select the 'name' and 'bmi' columns of the DataFrame, with the first row
print(data[['name', 'bmi']][:1])

dates = pd.date_range('20130101', periods=10)
print(dates)

df=pd.DataFrame(np.random.randn(10,4),index=dates,columns=list('ABCD'))
print(df)
print(df[df['A']>0])

#df.loc[row_indexer, column_indexer]
#loc=label based and iloc integer based
#len(df)=row/len(df.columns)
df.loc[:,'D']=np.array([5]*len(df))
print(df)

# Dropping a row by index
#df.drop(index=0, inplace=True)  # Drops the row at index 0

# Dropping multiple rows by label
#df.drop(labels=['row_label1', 'row_label2'], inplace=True)  # Drops rows with labels 'row_label1' and 'row_label2'
dates_df=pd.DataFrame(dates)
ts=pd.Timestamp('20130104')
df_new=pd.concat([df,dates_df],axis=1)
print(df_new)
print(df_new.shape)

# Scatter plot of 'bmi' against 'glu'
'''plt.scatter(df['bmi'], df['glu'])
plt.xlabel('BMI')
plt.ylabel('Glucose')
plt.title('Scatter Plot: BMI vs Glucose')
plt.show()'''

# Histogram for the 'age' column
'''df['age'].hist()
plt.xlabel('Age')
plt.ylabel('Frequency')
plt.title('Histogram: Age Distribution')
plt.show()'''

G = pd.read_excel('xyz.xlsx', sheet_name='Sheet1')
print(G.head())

H=pd.read_table('HR.txt')
f=H['Department'].value_counts()
f.plot(kind='bar')
plt.title('Department Distribution')
plt.xlabel('Department')
plt.ylabel('Count')
plt.show()

f.plot(kind='pie')
plt.title('Department Distribution (Pie Chart)')
plt.axis('equal') # Equal aspect ratio ensures that the pie chart is circular.
plt.show()