import sys

for line in sys.stdin:
 words = line.strip().split()
 for word in words:
    N = int(word)
    if N%2 == 0 and N > 0:
        print(N, '\t', 1)