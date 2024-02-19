import pandas as pd
data={'name':['Alice', 'Bob', 'Charlie', 'David'],
      'hieght':[160, 175, 162, 168],
      'qaulification':['Bachelor', 'Master', 'PhD', 'Bachelor']}
df=pd.DataFrame(data)
address_list=['123 Main St', '456 Oak St', '789 Elm St', '321 Pine St']
df['address']=address_list
print(df)
age_list = [23, 28, 25, 22]
df.insert(loc=2,column='age',value=age_list)
print(df)