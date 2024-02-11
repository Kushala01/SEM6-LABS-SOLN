import pandas as pd
import matplotlib.pyplot as plt

# Reading a text file with tab-separated values
H = pd.read_table('HR.txt')

# Extracting value counts for the 'Department' column
f = H['Department'].value_counts()

# Visualizing the distribution of categorical values using a bar plot
f.plot(kind='bar', color='skyblue', edgecolor='black')
plt.title('Department Distribution')
plt.xlabel('Department')
plt.ylabel('Count')
plt.show()

# Visualizing the above bar plot as a Pie chart
f.plot(kind='pie', autopct='%1.1f%%', startangle=90, colors=['lightcoral', 'lightgreen', 'lightblue'])
plt.title('Department Distribution (Pie Chart)')
plt.axis('equal')  # Equal aspect ratio ensures that the pie chart is circular.
plt.show()
