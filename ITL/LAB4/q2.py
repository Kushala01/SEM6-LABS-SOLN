#given array whose sum equals a specific target number
class q2:
    def __init__(self, arr):
        self.arr = arr  # Store the input array as an attribute of the object
    def searchPair(self, sum):
        n = len(self.arr)  # Get the length of the array
        for i in range(n): 
            res = []           # Create an empty list to store potential pair indices
            res.append(i)      # Add the index of the current outer loop element
            for j in range(i+1,n):  # Iterate over remaining elements (inner loop)
                res.append(j)      # Add the index of the inner loop element
                # Check if the current pair adds up to the desired sum
                if self.arr[i] + self.arr[j] == sum:
                    return res     # If found, immediately return the pair of indices
                res.remove(j)      # If not a match, remove the last added index
        return []  # If no pair is found, return an empty list
    
if __name__ == '__main__':
    qq2 = q2([1,2,5,7,8,9,3])  # Create an object of the class with the given array
    lst = qq2.searchPair(6)       # Search for a pair that sums to 6
    print(lst)                    # Print the indices of the found pair 