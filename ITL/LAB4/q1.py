#get all possible unique subsets from a set of distinct integers Input:[4,5,6] 
class Powerset:
    def find(self, arr):
        n = len(arr)  # Determine the number of elements in the input array
        ps_n = 2**n  # Calculate the number of subsets in the power set
        l = []  # Create an empty list to store the subsets
        # Iterate through all possible subset combinations (represented by values from 0 to 2^n - 1)
        for c in range(ps_n):
            l1 = []  # Create an empty list to store the current subset
            # Iterate over each element in the original array
            for j in range(n):
                # Create a bitmask where only the j-th bit is set
                bitmask = 1 << j 
                # Check if the j-th bit in 'c' is set, indicating inclusion in the subset
                if (c & bitmask): 
                    l1.append(arr[j])  # If set, add the element to the subset
            l.append(l1)  # Add the generated subset to the list of all subsets
        return l  # Return the complete power set

if __name__ == '__main__':
    # Get space-separated integers as input from the user
    arr = [int(x) for x in input('Enter array: ').split()] 
    ps = Powerset()  # Create an object of the Powerset class
    print(ps.find(arr))  # Call the 'find' method to generate and print the power set