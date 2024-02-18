import pandas as pd
from IPython.display import display

data = pd.read_csv("ans.csv", sep='\t')

print(data.head())  # Printing the first few rows of the DataFrame
print(data.tail(2))  # Printing the last two rows of the DataFrame

filteredRow = data[data['name'] == 'batman']  # Filtering rows where 'name' is 'batman'
print(filteredRow)  # Printing the filtered rows

replaced_row = data.replace('batman', 'spyderman')  # Replacing 'batman' with 'spyderman'
print(replaced_row)  # Printing the DataFrame with replacements

remove_col = data.drop('name', axis=1)  # Removing the 'name' column
print(remove_col)  # Printing the DataFrame with the column removed

print(data)  # Printing the original DataFrame to show it's unchanged

remove_row = data.iloc[1:2]  # Removing the row at index 1
print(remove_row)  # Printing the removed row

print(type(data))  

new_row = {'name': 'kushu', 'hieght': 121, 'weight': 33, 'bmi': 12}  # New row data
#new_row_added = data.append(new_row, ignore_index=True)  # Appending the new row to the DataFrame
new_row_added = pd.concat([data, pd.DataFrame([new_row])], ignore_index=True)  # Appending the new row to the DataFrame
print(new_row_added)  # Printing the DataFrame with the new row added

new_data=data.drop_duplicates(subset='name')

df=pd.DataFrame(data,index=['rank1','rank2','rank3'])
display(df)