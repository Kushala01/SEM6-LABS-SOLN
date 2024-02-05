import pandas as pd
import matplotlib.pyplot as plt
H = pd.read_csv('indians_diabetes.csv')
# Creating a cross-tabulation of two categorical variables
fa = pd.crosstab(H['Gender'], H['Attrition'])

# Visualizing the cross-tabulation as a bar plot
fa.plot(kind='bar', color=['skyblue', 'salmon'], edgecolor='black')
plt.title('Attrition by Gender')
plt.xlabel('Gender')
plt.ylabel('Count')
plt.legend(title='Attrition', loc='upper right', labels=['No', 'Yes'])
plt.show()