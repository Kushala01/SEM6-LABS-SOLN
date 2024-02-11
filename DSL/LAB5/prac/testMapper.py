import pandas as pd
df=pd.read_excel('German.xlsx', engine='openpyxl')
for country in df['creditAmount']:
	print ('%s\t%s' % (country, 1))