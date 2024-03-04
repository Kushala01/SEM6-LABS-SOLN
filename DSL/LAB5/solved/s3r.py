import fileinput

# Initialize counters
transactions_count = 0
sales_total = 0

# Loop through each line of input from file or stdin
for line in fileinput.input():
    # Split the line into key-value pairs
    data = line.strip().split("\t")
    # Check if the line has 2 fields (assuming it's properly formatted)
    if len(data) != 2:
        # Something has gone wrong. Skip this line.
        continue
    # Extract key and value
    current_key, current_value = data
    # Increment transaction count
    transactions_count += 1
    # Add current transaction value to total sales
    sales_total += float(current_value)

# Print the total number of transactions and the total sales amount
print(transactions_count, "\t", sales_total)
