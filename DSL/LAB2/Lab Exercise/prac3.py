import pandas as pd
data = {'Name': ['Annie', 'Diya', 'Charles', 'James', 'Emily'],
        'Quiz_1': [8.0, 9.0, 7.5, 8.5, 6.5],
        'In_Sem_1': [11.0, 14.0, 14.5, 13.0, 12.5],
        'Quiz_2': [9.5, 6.5, 8.5, 9.0, 9.0],
        'In_Sem_2': [12.5, 13.5, 14.5, 15.0, 13.0]}
df=pd.DataFrame(data)
df['total']=df[['Name','Quiz_1']].sum(axis=0)