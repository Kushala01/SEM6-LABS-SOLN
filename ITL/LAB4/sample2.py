class RomanNumeralConverter:
    """Converts integers to their Roman numeral representation."""

    def __init__(self):
        """
        Initializes the converter with lists of corresponding Roman numeral values and symbols.
        """
        self.values = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
        self.symbols = ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"]
      
    def int_to_roman(self, num):
        """
        Converts an integer to its Roman numeral representation.
        Args:
            num: The integer to convert (must be between 1 and 3999).
        Returns:
            The Roman numeral representation of the input integer.
        Raises:
            ValueError: If the input integer is out of range.
        """
        if not 1 <= num <= 3999:
            raise ValueError("Input number must be between 1 and 3999.")
        roman_num = ""
        i = 0  # Index to iterate through values and symbols
        while num > 0:
            # Find the largest Roman numeral value that fits in the remaining number
            count = num // self.values[i]
            # Add the corresponding symbol to the Roman numeral string, repeating it "count" times
            roman_num += self.symbols[i] * count
            # Subtract the used value from the remaining number
            num -= self.values[i] * count
            i += 1  # Move to the next value and symbol
        return roman_num
# Create an instance of the converter and call the method
converter = RomanNumeralConverter()
roman_numeral = converter.int_to_roman(1)
print(f"Roman numeral for 1: {roman_numeral}")  # Output: I
roman_numeral = converter.int_to_roman(4000)
print(f"Roman numeral for 4000: {roman_numeral}")  # Output: MMMM
