#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::string;

/**
 * I used the bitshift (>>) operator to isolate each bit in turn,
 * rather than using the algorithm described in the lecture.
 *
 * Questions:
 * 1. Q: What are the smallest negative decimal number and largest positive decimal
 *       number that can be stored in 16 bits using 2's complement format? Why?
 *    A: -32768, 32767. Because one bit is used for the sign, and 2^15 = 32768.
 *       The positive range appears to be one smaller, because it includes 0.
 * 2. Q: In C++, what procedure or operator allows you to extract a single character from a string?
 *    A: operator[]
 * 3. Q: In C++, what procedure or operator lets you concatenate characters into a single string?
 *    A: operator+
 * 4. Q: In C++, what procedure or operator lets you replace a character in a string with a different character?
 *    A: operator[]
 */

// Number of bits
const int SIZE = 16;

long maximumPositiveValue();
long minimumNegativeValue();
string convertDecimalToBinaryString(int);
bool in_range(int);
int convertCharToInt(char);
char getCarryFromThreeBitAdd(char, char, char);
char getSumFromThreeBitAdd(char, char, char);
string addBinaryNumbers(string, string);

// Lookup tables for three bit addition

// Say we are adding 0+1+1 binary.
// This addition gives a sum bit of 0 and a carry bit of 1.

// usage: sum = sumFromThreeBitAdd[0][1][1]; // sum: 0
// usage: carry  =  carryFromThreeBitAdd[0][1][1]; //  carry: 1
char carryFromThreeBitAdd[2][2][2] = {
	'0', // 0+0+0
	'0', // 0+0+1
	'0', // 0+1+0
	'1', // 0+1+1
	'0', // 1+0+0
	'1', // 1+0+1
	'1', // 1+1+0
	'1', // 1+1+1
};

char sumFromThreeBitAdd[2][2][2] = {
	'0', // 0+0+0
	'1', // 0+0+1
	'1', // 0+1+0
	'0', // 0+1+1
	'1', // 1+0+0
	'0', // 1+0+1
	'0', // 1+1+0
	'1', // 1+1+1
};

int main() {

    int input;

    cout << "Created Fall 2026 for CISP 310\n"
         << "by Michael Dorst\n";


    // loop until a valid input is entered
    while(true) {

        cout << "----------------------------------------\n"
             << "Please input an integer in the range "
			 << minimumNegativeValue()-1
			 << " < x < "
			 << maximumPositiveValue()+1
			 << "\n"
             << "> "
             << flush;

        cin >> input;

        cout << "----------------------------------------"
             << endl;

        if (in_range(input)) {
            break;
        } else {
            cout << "Value is out of range. Try again."
                 << endl;
        }
    }

    string result = convertDecimalToBinaryString(input);

    cout << input << " decimal is\n"
         << result << " binary.\n"
         << "----------------------------------------"
         << endl;
	
	system("pause");

    return 0;
}

// Maximum storable value in a signed integer of size SIZE
long maximumPositiveValue() {

	long biggestPositiveValue = pow(2, SIZE-1)-1; // SIZE of 8 gives 2^7 - 1
	
	return biggestPositiveValue;

}

// Minimum storable value in a signed integer of size SIZE
long minimumNegativeValue() {

	long smallestNegativeValue = -pow(2, SIZE-1); // SIZE of 8 gives 2^7
	
	return smallestNegativeValue;
}

// convert signed integer into string showing its 2's complement binary representation
string convertDecimalToBinaryString(int decimalValue) {
	// binaryString = "xxxxxxxx..." with SIZE 'x's
	string binaryString(SIZE, 'x');

	/**
	 * All positive integer values can be thought of as sums of powers of two.
	 * Eg. 100 = 64+32+4 = 2^6 + 2^5 + 2^2
	 * This algorithm will iteratively subtract these terms, largest to smallest.
	 */

	// This algorithm only works on positive values, so we need to take the absolute value
	// and store the sign for later, where we will do 2's complement on negative values.
	
	// True if decimalValue is negative, otherwise false.
	bool negative = decimalValue < 0;

	decimalValue = abs(decimalValue);

	// remainingMagnitude will represent the value which is left over after each
	// iterative subtraction.
	int remainingMagnitude = decimalValue;

    for (int i = SIZE-1; i >= 0; --i) {
		char bit;
		// Check if 2^i fits inside of remainingMagnitude
		if (remainingMagnitude >= pow(2, i)) {
			// If so, subtract 2^1 from remainingMagnitude, and make the current bit a 1
			remainingMagnitude -= pow(2, i);
			bit = '1';
		} else {
			// Otherwise, remainingMagnitude will stay the same, and the current bit will be 0
			bit = '0';
		}
		// Get the index of current bit
		int index = SIZE-1-i;
		// Add the current bit to binaryString
        binaryString[index] = bit;
    }

	// Convert to 2's complement if negative
	if (negative) {
		// Flip all the bits
		for (int i = 0; i < SIZE; ++i) {
			if (binaryString[i] == '0') {
				binaryString[i] = '1';
			} else {
				binaryString[i] = '0';
			}
		}
		// Create a string representing the binary value 1
		// Start with SIZE-1 0's (for SIZE=8, one = "0000000")
		string one(SIZE-1, '0');
		// Add a trailing 1
		one += "1";
		// Now, for SIZE=8, one = "00000001", which is 1 in 8-bit binary
		
		// Add 1 to binaryString
		binaryString = addBinaryNumbers(binaryString, one);
	}

	// add a space every four bits
	// substr(i, 4) starts at character i and gets the next 4 characters
	string binaryStringWithSpaces;
	for (int i = 0; i < SIZE; i += 4) {
		binaryStringWithSpaces += binaryString.substr(i, 4) + " ";
	}
	return binaryStringWithSpaces;
}

string addBinaryNumbers(string binaryNumber1, string binaryNumber2) {
	char carryBit = '0';
	// Initialize sum to be "xxxxxx..." of length SIZE
	string resultantSum(SIZE, 'x');
	// Iterate over numbers in reverse order (LSB to MSB)
	// Every iteration will add three bits for the current column (power of 2) in the binary addition.
	// The top bit will be the carry bit from the previous column addition, the middle bit will come from
	// binaryNumber2 and the bottom bit will come from binaryNumber1.
	// We will store the result in this column of the resultantSum.
	//
	// eg. (using SIZE=4 bits, showing the second iteration of 10d + 6d)
	//     store carry---v  v---read carry
	//        carry:   0[1][0](0) <-- we seed the carry bit with 0
	//          10d:   1 0 [1] 0
	//           6d: + 0 1 [1] 0
	//               -----------
	// resultantSum:   x x [0] 0
	//      store result ---^
	for (int i = SIZE-1; i >= 0; --i) {
		// Get the sum of binaryNumber1[i], binaryNumber[2] and carryBit using the lookup table
		resultantSum[i] = getSumFromThreeBitAdd(binaryNumber1[i], binaryNumber2[i], carryBit);
		carryBit = getCarryFromThreeBitAdd(binaryNumber1[i], binaryNumber2[i], carryBit);
	}
	return resultantSum;
}

char getCarryFromThreeBitAdd(char bit1, char bit2, char bit3) {
	// Convert bits to integers
	int integerBit1 = convertCharToInt(bit1);
	int integerBit2 = convertCharToInt(bit2);
	int integerBit3 = convertCharToInt(bit3);

	// Use the lookup table to find and return the carry
	char carry = carryFromThreeBitAdd[integerBit1][integerBit2][integerBit3];
	return carry;
}

char getSumFromThreeBitAdd(char bit1, char bit2, char bit3) {
	// Convert bits to integers
	int integerBit1 = convertCharToInt(bit1);
	int integerBit2 = convertCharToInt(bit2);
	int integerBit3 = convertCharToInt(bit3);

	// Use the lookup table to find and return the carry
	char sum = sumFromThreeBitAdd[integerBit1][integerBit2][integerBit3];
	return sum;
}

int convertCharToInt(char c)  {
	int integerValue;
	if (c == '1') {
		integerValue = 1;
	} else {
		integerValue = 0;
	}
	return integerValue;
}

// true if value can fit in a signed integer with SIZE bits
bool in_range(int value) {
	
	bool greaterThanMinimum = (value >= minimumNegativeValue());
	bool lessThanMaximum = (value <= maximumPositiveValue());
	
	// true when between maximum and minimum values
	return (greaterThanMinimum && lessThanMaximum);
	
}
