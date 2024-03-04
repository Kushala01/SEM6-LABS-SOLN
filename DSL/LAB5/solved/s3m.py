import fileinput

# Loop through each line of input from file or stdin
for line in fileinput.input():
    # Split the line into fields
    data = line.strip().split("\t")
    # Check if the line has 6 fields (assuming it's properly formatted)
    if len(data) == 6:
        # Extract location and cost fields
        date, time, location, item, cost, payment = data
        # Output location and cost as key-value pairs
        print("{0}\t{1}".format(location, cost))
