// Based on the provided exam and reference code.
#include <iostream>
#include <string>

bool parseNumber(const std::string& token, long long& number)
{
    std::size_t position = 0;
    bool negative = false;
    if (!token.empty() && (token[0] == '+' || token[0] == '-')) {
        negative = token[0] == '-';
        position = 1;
    }
    if (position == token.size()) return false;
    long long value = 0;
    for (; position < token.size(); ++position) {
        if (token[position] < '0' || token[position] > '9') return false;
        const int digit = token[position] - '0';
        if (value > (2147483647LL - digit) / 10) return false;
        value = value * 10 + digit;
    }
    if (negative && value != 0) return false;
    number = value;
    return true;
}

int main()
{
    long long number = 0;
    std::string token;
    while (std::cin >> token) {
        if (parseNumber(token, number)) break;
        std::cout << "You should input a positive integer\n";
    }
    if (!std::cin || !parseNumber(token, number)) return 0;
    unsigned iteration = 0;
    while (number >= 10) {
        ++iteration;
        for (unsigned index = 0; index < iteration; ++index) std::cout << "f(";
        std::cout << 'n';
        for (unsigned index = 0; index < iteration; ++index) std::cout << ')';
        std::cout << '=';
        long long divisor = 1;
        for (long long rest = number; rest >= 10; rest /= 10) divisor *= 10;
        long long sum = 0;
        while (divisor > 0) {
            const long long digit = number / divisor % 10;
            std::cout << digit;
            sum += digit;
            divisor /= 10;
            if (divisor > 0) std::cout << '+';
        }
        std::cout << '=' << sum << '\n';
        number = sum;
    }
    std::cout << "The summing digit is:" << number << '\n';
    return 0;
}
