#include <iostream>
#include <memory>
#include <new>
#include <string>
using namespace std;

void printTerm(long long term) {
    if (term < 0) cout << '(' << term << ')';
    else cout << term;
}
string multiplyDecimal(unsigned long long value, unsigned long long factor) {
    string digits = to_string(value);
    unsigned long long carry = 0;
    for (size_t i = digits.size(); i > 0; --i) {
        const unsigned long long product = (digits[i - 1] - '0') * factor + carry;
        digits[i - 1] = static_cast<char>('0' + product % 10);
        carry = product / 10;
    }
    while (carry) {
        digits.insert(digits.begin(), static_cast<char>('0' + carry % 10));
        carry /= 10;
    }
    return digits;
}

int main() {
    long long a, d, n;
    cout << "Please enter the first term(a1), the common difference(d) and the number of terms(n):\n";
    if (!(cin >> a >> d >> n) || a < -2147483649LL || a > 2147483647LL ||
        d < -2147483649LL || d > 2147483647LL || n < 1 || n > 2147483647LL) {
        cout << "Invalid input\n";
        return 1;
    }
    unique_ptr<long long[]> terms;
    try {
        terms.reset(new long long[static_cast<size_t>(n)]);
    } catch (const bad_alloc &) {
        cout << "Not enough memory for the requested array\n";
        return 1;
    }
    for (long long i = 0; i < n; ++i) terms[static_cast<size_t>(i)] = a + i * d;
    cout << "The arithmetical series: ";
    for (long long i = 0; i < n; ++i) {
        if (i) cout << " + ";
        printTerm(terms[static_cast<size_t>(i)]);
    }
    // n*(first+last)/2; divide an even factor first, then multiply in decimal.
    // This also avoids overflow in the sum when the individual terms fit.
    long long endpoints = terms[0] + terms[static_cast<size_t>(n - 1)];
    unsigned long long count = static_cast<unsigned long long>(n);
    if (count % 2 == 0) count /= 2;
    else endpoints /= 2;
    const bool negative = endpoints < 0;
    const unsigned long long magnitude = static_cast<unsigned long long>(negative ? -endpoints : endpoints);
    cout << " = ";
    if (negative) cout << "(-";
    cout << multiplyDecimal(magnitude, count);
    if (negative) cout << ')';
    cout << '\n';
}
