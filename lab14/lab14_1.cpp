// Revised from the original 2021 Lab 14.1: precedence and zero operands are preserved.
#include <cstdint>
#include <iostream>
#include <string>

// Decimal magnitudes keep intermediate products exact even when they exceed
// 64 bits. Each literal remains within the handout's nonnegative int32 range.
class Natural {
public:
    explicit Natural(std::uint32_t value = 0) : digits(std::to_string(value)) {}

    int compare(const Natural& other) const {
        if (digits.size() != other.digits.size())
            return digits.size() < other.digits.size() ? -1 : 1;
        return digits == other.digits ? 0 : (digits < other.digits ? -1 : 1);
    }

    void add(const Natural& other) {
        std::string result;
        std::size_t a = digits.size(), b = other.digits.size();
        unsigned carry = 0;
        while (a || b || carry) {
            unsigned sum = carry;
            if (a) sum += static_cast<unsigned>(digits[--a] - '0');
            if (b) sum += static_cast<unsigned>(other.digits[--b] - '0');
            result.push_back(static_cast<char>('0' + sum % 10));
            carry = sum / 10;
        }
        assign_reversed(result);
    }

    // Precondition: this magnitude is at least other.
    void subtract(const Natural& other) {
        std::string result;
        std::size_t a = digits.size(), b = other.digits.size();
        int borrow = 0;
        while (a) {
            int digit = digits[--a] - '0' - borrow;
            if (b) digit -= other.digits[--b] - '0';
            borrow = digit < 0;
            if (borrow) digit += 10;
            result.push_back(static_cast<char>('0' + digit));
        }
        assign_reversed(result);
    }

    void multiply(std::uint32_t factor) {
        std::string result;
        std::uint64_t carry = 0;
        for (std::size_t i = digits.size(); i > 0; --i) {
            carry += static_cast<std::uint64_t>(digits[i - 1] - '0') * factor;
            result.push_back(static_cast<char>('0' + carry % 10));
            carry /= 10;
        }
        while (carry) {
            result.push_back(static_cast<char>('0' + carry % 10));
            carry /= 10;
        }
        assign_reversed(result);
    }

    std::uint32_t divide(std::uint32_t divisor) {
        std::uint64_t remainder = 0;
        for (std::size_t i = 0; i < digits.size(); ++i) {
            remainder = remainder * 10 + static_cast<unsigned>(digits[i] - '0');
            digits[i] = static_cast<char>('0' + remainder / divisor);
            remainder %= divisor;
        }
        normalize();
        return static_cast<std::uint32_t>(remainder);
    }

    const std::string& str() const { return digits; }

private:
    std::string digits;
    void normalize() {
        const std::size_t start = digits.find_first_not_of('0');
        digits = start == std::string::npos ? "0" : digits.substr(start);
    }
    void assign_reversed(const std::string& reversed) {
        digits.assign(reversed.rbegin(), reversed.rend());
        normalize();
    }
};

class SignedSum {
public:
    SignedSum() : magnitude(0), negative(false) {}
    void add_term(const Natural& term, bool subtract) {
        if (negative == subtract) {
            magnitude.add(term);
        } else if (magnitude.compare(term) >= 0) {
            magnitude.subtract(term);
        } else {
            Natural difference = term;
            difference.subtract(magnitude);
            magnitude = difference;
            negative = subtract;
        }
        if (magnitude.str() == "0") negative = false;
    }
    bool in_int32_range() const {
        return magnitude.compare(Natural(negative ? 2147483648u : 2147483647u)) <= 0;
    }
    void print() const {
        if (negative) std::cout << '-';
        std::cout << magnitude.str() << '\n';
    }
private:
    Natural magnitude;
    bool negative;
};

bool read_number(const std::string& expression, std::size_t& position,
                 std::uint32_t& number) {
    number = 0;
    const std::size_t start = position;
    while (position < expression.size() && expression[position] >= '0'
           && expression[position] <= '9') {
        const unsigned digit = expression[position] - '0';
        if (number > (2147483647u - digit) / 10) return false;
        number = number * 10 + digit;
        ++position;
    }
    return position != start;
}

int main() {
    std::cout << "Please enter the arithmetic: ";
    std::string expression;
    if (!std::getline(std::cin, expression)) return 0;
    if (!expression.empty() && expression.back() == '\r') expression.pop_back();
    std::size_t position = 0;
    SignedSum sum;
    bool subtract = false;
    while (true) {
        std::uint32_t number;
        if (!read_number(expression, position, number)) {
            std::cout << "error\n";
            return 1;
        }
        Natural term(number);
        while (position < expression.size() &&
               (expression[position] == '*' || expression[position] == '/'
                || expression[position] == '%')) {
            const char operation = expression[position++];
            if (!read_number(expression, position, number)
                || (operation != '*' && number == 0)) {
                std::cout << "error\n";
                return 1;
            }
            if (operation == '*') term.multiply(number);
            else {
                const std::uint32_t remainder = term.divide(number);
                if (operation == '%') term = Natural(remainder);
            }
        }
        sum.add_term(term, subtract);
        if (position == expression.size()) break;
        const char operation = expression[position++];
        if (operation != '+' && operation != '-') {
            std::cout << "error\n";
            return 1;
        }
        subtract = operation == '-';
    }
    if (!sum.in_int32_range()) {
        std::cout << "error\n";
        return 1;
    }
    sum.print();
    return 0;
}
