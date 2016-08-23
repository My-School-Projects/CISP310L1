#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::flush;

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
        return value;
    }
    static bool in_range(int64_t value) {
        return value >= -32768 && value < 32768;
    }
    bin16_t() {
        for (int i = 0; i < 17; ++i) {
            value[i] = NULL;
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
