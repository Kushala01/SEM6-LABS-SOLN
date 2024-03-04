#!/usr/bin/env python
import pandas as pd
import sys
df = pd.read_excel('german.xlsx', engine = 'openpyxl')
for country in df['CreditAmount']:
	print('%d\t%d'%(country, 1))