import pandas as pd
from IPython.display import display

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
print(remove_col)

# Print the original DataFrame to show it's unchanged
print(data)

# Remove the row at index 1 from the DataFrame
remove_row = data.iloc[1:2]
print(remove_row)

# Check the type of the DataFrame
print(type(data))

# Define a new row of data
new_row = {'name': 'kushu', 'hieght': 121, 'weight': 33, 'bmi': 12}

# Append the new row to the DataFrame
new_row_added = pd.concat([data, pd.DataFrame([new_row])], ignore_index=True)
print(new_row_added)

# Drop duplicate rows based on the 'name' column
new_data = data.drop_duplicates(subset='name')

# Create a new DataFrame with custom index labels
df = pd.DataFrame(data, index=['rank1', 'rank2', 'rank3'])

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