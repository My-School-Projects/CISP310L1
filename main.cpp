#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::flush;

/**
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

class bin16_t {
private:
    char value[17]; // 16 + NULL
public:
    // int16_t is a 16 bit signed integer.
    // inputs should be verified before `set` is called.
    void set(int16_t v) {
        for (int i = 0; i < 16; ++i) {
            value[15-i] = (v >> i) & 1 ? '1' : '0';
        }
    }
    std::string get_string() {
        std::string v = value;
        // add a space every four bits
        return v.substr(0, 4) + " "
             + v.substr(4, 4) + " "
             + v.substr(8, 4) + " "
             + v.substr(12);
    }
    static bool in_range(int64_t value) {
        return value >= -32768 && value < 32768;
    }
    bin16_t() {
        for (int i = 0; i < 17; ++i) {
            value[i] = 0;
        }
    }
};

int main() {

    int64_t input;
    bin16_t value;

    cout << "Created Fall 2026 for CISP 310\n"
         << "by Michael Dorst\n";


    // loop until a valid input is entered
    while(true) {

        cout << "----------------------------------------\n"
             << "Please input an integer in the range -32769 < x < 32768\n"
             << "> "
             << flush;

        cin >> input;

        cout << "----------------------------------------"
             << endl;

        if (bin16_t::in_range(input)) {
            break;
        } else {
            cout << "Value is out of range. Try again."
                 << endl;
        }
    }

    value.set(input);

    cout << input << " decimal is\n"
         << value.get_string() << " binary.\n"
         << "----------------------------------------"
         << endl;

    return 0;
}
