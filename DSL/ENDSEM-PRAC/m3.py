import sys
import pandas as pd
import argparse

fnames = ["heart_disease_data.csv","covid_19_data.csv","German_Credit.xlsx","example.txt"]

parser = argparse.ArgumentParser()
parser.add_argument('-c','--choice')
args = parser.parse_args()

choice = int(args.choice)
if choice==3:
    df=pd.read_excel(fnames[choice-1])
elif choice==4:
    df = pd.read_csv(fnames[choice-1],sep='\t',names=['Date','Time','City','Category','Price','Card'])
else:
    df = pd.read_csv(fnames[choice-1])

columns = ['target','Province/State','Creditability','City']
col = df[columns[choice-1]].astype(str)
col.dropna(axis=0,inplace=True)
for line in col:
    line = line.strip()
    words = line.split()
    for word in words:
       print('{}\t{}'.format(word, 1))