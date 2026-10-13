// 2024 P1130291: exact combinations, with a recursive calculation.
#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

class Natural {
    string digits;
public:
    Natural() : digits("1") {}
    void multiply(uint32_t factor) {
        uint64_t carry = 0;
        for (size_t i = digits.size(); i > 0; --i) {
            carry += static_cast<uint64_t>(digits[i - 1] - '0') * factor;
            digits[i - 1] = static_cast<char>('0' + carry % 10);
            carry /= 10;
        }
        while (carry) {
            digits.insert(digits.begin(), static_cast<char>('0' + carry % 10));
            carry /= 10;
        }
    }
    void divide(uint32_t divisor) {
        uint64_t remainder = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            remainder = remainder * 10 + static_cast<unsigned>(digits[i] - '0');
            digits[i] = static_cast<char>('0' + remainder / divisor);
            remainder %= divisor;
        }
        const size_t first = digits.find_first_not_of('0');
        digits = first == string::npos ? "0" : digits.substr(first);
    }
    const string &text() const { return digits; }
};

// Process the binomial recurrence in order; split the call tree to keep
// recursion depth logarithmic while preserving exact division at each step.
void combinationSteps(uint32_t m, uint32_t n, uint32_t first, uint32_t last, Natural &result) {
    if (first > last) return;
    if (first == last) {
        result.multiply(m - n + first);
        result.divide(first);
        return;
    }
    const uint32_t middle = first + (last - first) / 2;
    combinationSteps(m, n, first, middle, result);
    combinationSteps(m, n, middle + 1, last, result);
}
int main() {
    long long m, n;
    if (!(cin >> m >> n) || m < 0 || n < 0 || n > m || m > 4294967295LL) {
        cout << "error\n";
        return 1;
    }
    if (n > m - n) n = m - n;
    Natural result;
    combinationSteps(static_cast<uint32_t>(m), static_cast<uint32_t>(n), 1,
                     static_cast<uint32_t>(n), result);
    cout << "ans: " << result.text() << '\n';
}
