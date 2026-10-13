#include <iostream>
#include <limits>

bool readOperands(int& first, int& second)
{
    std::cout << "Enter a and b: ";
    while (true) {
        if (std::cin >> first >> second) {
            if (first >= 0 && second >= 0) return true;
        } else {
            if (std::cin.eof()) return false;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Wrong numbers. Enter two integers again.\n";
    }
}

bool integerPower(int base, int exponent, long long& result)
{
    result = 1; // The Review's initial value also defines 0^0 as 1.
    long long factor = base;
    while (exponent > 0) {
        if (exponent % 2 != 0) {
            if (factor != 0 && result > std::numeric_limits<long long>::max() / factor) return false;
            result *= factor;
        }
        exponent /= 2;
        if (exponent > 0) {
            if (factor != 0 && factor > std::numeric_limits<long long>::max() / factor) return false;
            factor *= factor;
        }
    }
    return true;
}

int main()
{
    std::cout << "Welcome to use our calculator. Type 'e' to exit.\n";
    char operation = 0;
    while (std::cin.get(operation)) {
        int first = 0;
        int second = 0;
        long long result = 0;
        switch (operation) {
        case 'e':
            std::cout << "Goodbye~\n";
            return 0;
        case '+': case '-': case '*': case '^':
            if (!readOperands(first, second)) return 0;
            switch (operation) {
            case '+': result = static_cast<long long>(first) + second; break;
            case '-': result = static_cast<long long>(first) - second; break;
            case '*': result = static_cast<long long>(first) * second; break;
            case '^':
                if (!integerPower(first, second, result)) {
                    std::cout << "Calculation result is out of range.\n\n";
                    continue;
                }
                break;
            }
            std::cout << "Calculation result: a " << operation << " b = " << result << "\n\n";
            break;
        case '\n': case '\r': case '\t': case ' ':
            break;
        default:
            std::cout << "Incorrect mathematical operator entered. Enter a new one.\n";
            break;
        }
    }
    return 0;
}
