import sys

def f(x):
    return 4.0 / (1.0 + x * x)

for line in sys.stdin:
    word = line.strip().strip()
    N = int(words[0])
    deltaX = 1.0 / N
    for i in range(0, N):
        print("1\t%1.10f" % (f(i * deltaX) * deltaX))