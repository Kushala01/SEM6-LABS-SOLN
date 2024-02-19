import pandas as pd
# Create a data frame
data = {'Name': ['Annie', 'Diya', 'Charles', 'James', 'Emily'],
        'Quiz_1': [8.0, 9.0, 7.5, 8.5, 6.5],
        'In_Sem_1': [11.0, 14.0, 14.5, 13.0, 12.5],
        'Quiz_2': [9.5, 6.5, 8.5, 9.0, 9.0],
        'In_Sem_2': [12.5, 13.5, 14.5, 15.0, 13.0]}

df = pd.DataFrame(data)

# Insert a column 'Total' and calculate the total marks
df['Total'] = df[['Quiz_1', 'In_Sem_1', 'Quiz_2', 'In_Sem_2']].sum(axis=1)

# Calculate the mean for each subject and insert a row 'Subject Mean'
subject_mean = df[['Quiz_1', 'In_Sem_1', 'Quiz_2', 'In_Sem_2']].mean()
subject_mean_row = pd.DataFrame({'Name': ['Subject Mean'], 
                                 'Quiz_1': [subject_mean['Quiz_1']], 
                                 'In_Sem_1': [subject_mean['In_Sem_1']],
                                 'Quiz_2': [subject_mean['Quiz_2']], 
                                 'In_Sem_2': [subject_mean['In_Sem_2']],
                                 'Total': [df['Total'].mean()]})
#df = df.append(pd.Series({'Name': 'Subject Mean', **subject_means, 'Total': df['Total'].mean()}), ignore_index=True)

df = pd.concat([df, subject_mean_row], ignore_index=True)

# Display the resulting data frame
print(df)