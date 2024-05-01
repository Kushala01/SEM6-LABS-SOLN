from itertools import groupby
from operator import itemgetter
import sys

def read_input(file, separator='\t'):
    for line in file:
        yield line.rstrip().split(separator, 1)

def main(separator='\t'):
    # Read input data from stdin
    data = read_input(sys.stdin, separator=separator)
    
    # Group data by the first item (key)
    grouped_data = groupby(data, itemgetter(0))
    
    # Process each group
    for key, group in grouped_data:
        total_count = 0
        for _, count_str in group:
            total_count += int(count_str)
        
        # Print key and total count
        print(f"{key}{separator}{total_count}")

if __name__ == "__main__":
    main()