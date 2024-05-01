from __future__ import print_function
import sys

mostFreq=[]
currMaxCount=-1

for line in sys.stdin:
    line=line.strip().lower()
    word,count=line.split('\t',1)
    count=int(count)
    if count>currMaxCount:
        currMaxCount=count
        mostFreq=[word]
    elif count==currMaxCount:
        mostFreq.append(word)

for i in mostFreq:
    print("%s\t%d"%(i,currMaxCount))