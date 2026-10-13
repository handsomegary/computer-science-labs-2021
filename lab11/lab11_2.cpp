// Based on the original lab; pointer-only matrix access, exact wide results.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Ten products of signed 64-bit inputs can exceed both 64 and 128 bits.
// This small base-1e9 integer keeps all valid input products exact in standard C++11.
class Integer {
    static const unsigned long long base = 1000000000ULL;
    vector<unsigned long long> digits;
    bool negative;
    void normalize() {
        while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
        if (digits.size() == 1 && digits.front() == 0) negative = false;
    }
    int compare_magnitude(const Integer& other) const {
        if (digits.size() != other.digits.size()) return digits.size() > other.digits.size() ? 1 : -1;
        for (size_t i = digits.size(); i > 0; --i)
            if (*(digits.data() + i - 1) != *(other.digits.data() + i - 1))
                return *(digits.data() + i - 1) > *(other.digits.data() + i - 1) ? 1 : -1;
        return 0;
    }
public:
    explicit Integer(long long value = 0) : negative(value < 0) {
        unsigned long long magnitude = value < 0 ? static_cast<unsigned long long>(-(value + 1)) + 1
                                                 : static_cast<unsigned long long>(value);
        do { digits.push_back(magnitude % base); magnitude /= base; } while (magnitude);
    }
    Integer operator*(const Integer& other) const {
        Integer result;
        result.digits.assign(digits.size() + other.digits.size(), 0);
        result.negative = negative != other.negative;
        for (size_t i = 0; i < digits.size(); ++i) {
            unsigned long long carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                unsigned long long value = *(result.digits.data() + i + j) + carry;
                if (j < other.digits.size()) value += *(digits.data() + i) * *(other.digits.data() + j);
                *(result.digits.data() + i + j) = value % base;
                carry = value / base;
            }
        }
        result.normalize();
        return result;
    }
    void add(const Integer& other) {
        if (negative == other.negative) {
            const size_t length = digits.size() > other.digits.size() ? digits.size() : other.digits.size();
            digits.resize(length + 1, 0);
            unsigned long long carry = 0;
            for (size_t i = 0; i < length; ++i) {
                unsigned long long value = *(digits.data() + i) + carry;
                if (i < other.digits.size()) value += *(other.digits.data() + i);
                *(digits.data() + i) = value % base;
                carry = value / base;
            }
            *(digits.data() + length) = carry;
        } else {
            if (compare_magnitude(other) < 0) {
                Integer result = other;
                result.add(*this);
                *this = result;
                return;
            }
            long long borrow = 0;
            for (size_t i = 0; i < digits.size(); ++i) {
                long long value = static_cast<long long>(*(digits.data() + i)) - borrow;
                if (i < other.digits.size()) value -= static_cast<long long>(*(other.digits.data() + i));
                borrow = value < 0;
                if (borrow) value += base;
                *(digits.data() + i) = static_cast<unsigned long long>(value);
            }
        }
        normalize();
    }
    string text() const {
        string result = negative ? "-" : "";
        result += to_string(digits.back());
        for (size_t i = digits.size() - 1; i > 0; --i) {
            const string part = to_string(*(digits.data() + i - 1));
            result += string(9 - part.size(), '0') + part;
        }
        return result;
    }
};

int main() {
    int rows1, columns1, rows2, columns2;
    cout << "Enter rows and columns for first matrix:\n";
    if (!(cin >> rows1 >> columns1)) return 0;
    cout << "Enter rows and columns for second matrix:\n";
    if (!(cin >> rows2 >> columns2)) return 0;
    if (rows1 < 1 || rows1 > 10 || columns1 < 1 || columns1 > 10 ||
        rows2 < 1 || rows2 > 10 || columns2 < 1 || columns2 > 10 || columns1 != rows2) {
        cout << "Cannot multiply these two matrixes.\n";
        return 0;
    }
    vector<long long> first(rows1 * columns1), second(rows2 * columns2);
    cout << "\nEnter matrix 1:\n";
    for (long long *p = first.data(); p != first.data() + first.size(); ++p)
        if (!(cin >> *p)) return 0;
    cout << "\nEnter matrix 2:\n";
    for (long long *p = second.data(); p != second.data() + second.size(); ++p)
        if (!(cin >> *p)) return 0;
    cout << "\nOutput Matrix:\n";
    for (int row = 0; row < rows1; ++row) {
        for (int column = 0; column < columns2; ++column) {
            Integer sum;
            for (int k = 0; k < columns1; ++k)
                sum.add(Integer(*(first.data() + row * columns1 + k)) *
                        Integer(*(second.data() + k * columns2 + column)));
            if (column) cout << ' ';
            cout << sum.text();
        }
        cout << '\n';
    }
}
