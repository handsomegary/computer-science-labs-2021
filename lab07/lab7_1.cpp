#include <iostream>
#include <string>
using namespace std;

string normalize(const string &value) {
    const size_t first = value.find_first_not_of('0');
    return first == string::npos ? "0" : value.substr(first);
}
bool lessEqual(const string &a, const string &b) {
    return a.size() != b.size() ? a.size() < b.size() : a <= b;
}
string multiply(const string &value, unsigned factor) {
    string result = value;
    unsigned carry = 0;
    for (size_t i = result.size(); i > 0; --i) {
        const unsigned digit = (result[i - 1] - '0') * factor + carry;
        result[i - 1] = static_cast<char>('0' + digit % 10);
        carry = digit / 10;
    }
    while (carry) {
        result.insert(result.begin(), static_cast<char>('0' + carry % 10));
        carry /= 10;
    }
    return normalize(result);
}
string subtract(string a, const string &b) {
    int borrow = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        const size_t at = a.size() - 1 - i;
        int digit = a[at] - '0' - borrow;
        if (i < b.size()) digit -= b[b.size() - 1 - i] - '0';
        borrow = digit < 0;
        if (borrow) digit += 10;
        a[at] = static_cast<char>('0' + digit);
    }
    return normalize(a);
}

// Decimal longhand square root: one recursive call per pair of digits.
// Integer arithmetic gives exact truncation even for 2^63-1.
string squareRoot(const string &pairs, size_t at, const string &root, const string &remainder) {
    if (at == pairs.size()) return root;
    const string rest = normalize(remainder + pairs.substr(at, 2));
    unsigned digit = 9;
    string product;
    while (true) {
        // (20 * root + digit) * digit; append digit to (2 * root).
        product = multiply(normalize(multiply(root, 2) + static_cast<char>('0' + digit)), digit);
        if (lessEqual(product, rest)) break;
        --digit;
    }
    return squareRoot(pairs, at + 2, normalize(root + static_cast<char>('0' + digit)), subtract(rest, product));
}

bool validInput(const string &value) {
    if (value.empty()) return false;
    for (size_t i = 0; i < value.size(); ++i)
        if (value[i] < '0' || value[i] > '9') return false;
    return lessEqual(normalize(value), "9223372036854775807");
}

int main() {
    string input;
    cout << "Enter a number: ";
    while (cin >> input) {
        if (validInput(input)) break;
        cout << "The number is out of range. Please enter again: ";
    }
    if (!cin) return 0;
    string pairs = normalize(input) + string(20, '0');
    if (pairs.size() % 2) pairs.insert(pairs.begin(), '0');
    string root = squareRoot(pairs, 0, "0", "0");
    if (root.size() <= 10) root.insert(0, 11 - root.size(), '0');
    cout << root.substr(0, root.size() - 10) << '.' << root.substr(root.size() - 10) << '\n';
}
