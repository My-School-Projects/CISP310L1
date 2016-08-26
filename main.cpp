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
	// s = "xxxxxxxx..." with SIZE 'x's
	string s(SIZE, 'x');
    for (int i = 0; i < SIZE; ++i) {
		char bit;
		// shift bits to the right i spaces
		// eg. given decimalValue = 0101 0010b, i = 3
		// shiftedRight = 0000 1010b
		short shiftedRight = (decimalValue >> i);
		// perform bitwize AND with 0000 0001b
		// REASON: This isolates the last bit of decimalValue, once it's been shifted i bits.
		// Because i goes from 0 to SIZE-1, this isolates each bit of the integer.
		int currentBit = shiftedRight & 1;
		if (currentBit == 1) {
			bit = '1';
		} else {
			bit = '0';
		}
		int x = SIZE-1-i;
        s[x] = bit;
    }
	// add a space every four bits
	// substr(x, 4) starts at character x and gets the next 4 characters
	s = s.substr(0, 4) + " "
        + s.substr(4, 4) + " "
        + s.substr(8, 4) + " "
        + s.substr(12);
	return s;
}

// true if value can fit in a signed integer with SIZE bits
bool in_range(int value) {
	
	bool greaterThanMinimum = (value >= minimumNegativeValue());
	bool lessThanMaximum = (value <= maximumPositiveValue());
	
	// true when between maximum and minimum values
	return (greaterThanMinimum && lessThanMaximum);
	
}
