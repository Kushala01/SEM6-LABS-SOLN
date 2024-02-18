import pandas as pd  # Importing the Pandas library and aliasing it as pd
my_list = ['mariya', 'spongebob', 'batman']  # Creating a list of names
print(my_list)  # Printing the list of names

# Creating a dictionary with column names as keys and lists as values
titled_col = {
    "name": my_list,
    "hieght": [172, 134, 122],  # Typo corrected from "hieght" to "height"
    'weight': [23, 43, 55]
}

# Creating a DataFrame from the dictionary
data = pd.DataFrame(titled_col)

# Accessing the 'weight' column of the DataFrame
weights = data['weight']

print(data)  # Printing the DataFrame
print('Weights are:\n', weights)  # Printing the 'weight' column

# Accessing the weight of Batman using DataFrame indexing
wgtBatman = data['weight'][2]
print('Weight for Batman is:\n', wgtBatman)  # Printing Batman's weight

# Accessing Spongebob's height using DataFrame indexing
spongebob_height = data.iloc[1]["hieght"]
print('Details of Spongebob are:\n', spongebob_height)

# Calculating BMI for each individual and adding a new column 'bmi' to the DataFrame
bmi = []
for i in range(len(data)):
    bmi_score = data['weight'][i] / (data["hieght"][i] ** 2)
    bmi.append(bmi_score)
data['bmi'] = bmi

print(data)  # Printing the DataFrame with the 'bmi' column added

# Exporting the DataFrame to a CSV file with tab separator
data.to_csv("ans.csv", sep='\t')
# data.to_csv("ans.txt", sep='\t')  # This line is commented out to prevent writing to a text file