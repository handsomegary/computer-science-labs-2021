// Optional practical big-integer extension, NOT the template debugging answer.
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string factorial(unsigned n) {
    string value = "1";
    for (unsigned factor = 2; factor <= n; ++factor) {
        unsigned carry = 0;
        for (size_t i = value.size(); i > 0; --i) {
            const unsigned digit = (value[i - 1] - '0') * factor + carry;
            value[i - 1] = static_cast<char>('0' + digit % 10);
            carry = digit / 10;
        }
        while (carry) {
            value.insert(value.begin(), static_cast<char>('0' + carry % 10));
            carry /= 10;
        }
    }
    return value;
}

int main() {
    unsigned a, b, c;
    cout << "Enter 3 nums: ";
    if (!(cin >> a >> b >> c)) return 1;
    // Bound only the optional extension's runtime/output, not its precision.
    if (a < 1 || b < 1 || c < 1 || a > 10000 || b > 10000 || c > 10000) {
        cout << "Input out of practical range (1-10000).\n";
        return 1;
    }
    cout << "GCD of " << factorial(a) << " and " << factorial(b) << " and "
         << factorial(c) << " is " << factorial(min(a, min(b, c))) << '\n';
}
