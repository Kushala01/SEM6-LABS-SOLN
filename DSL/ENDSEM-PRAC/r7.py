import sys

sum = 0.0
for line in sys.stdin:
    line = line.strip()
    word, count = line.split('\t', 1)
    count = float(count)
    sum += count
print('%1.10f\t0' % sum)