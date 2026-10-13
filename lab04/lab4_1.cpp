#include <iostream>
#include <limits>

int main()
{
    long long number = 0;
    std::cout << "Enter a number: ";
    while (true) {
        if (std::cin >> number) {
            if (number >= 2 && number <= 2147483647LL) {
                break;
            }
        } else {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Please enter a correct number: ";
    }

    std::cout << number << " = ";
    long long remaining = number;
    long long factor = 2;
    bool first = true;
    // Once factor exceeds sqrt(remaining), the remaining value is prime.
    while (factor <= remaining / factor) {
        while (remaining % factor == 0) {
            if (!first) {
                std::cout << '*';
            }
            std::cout << factor;
            first = false;
            remaining /= factor;
        }
        ++factor;
    }
    if (remaining > 1) {
        if (!first) {
            std::cout << '*';
        }
        std::cout << remaining;
    }
    std::cout << '\n';
    return 0;
}
