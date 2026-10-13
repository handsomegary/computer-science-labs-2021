#include <iostream>

int main()
{
    long long binary = 0;
    std::cout << "Please input an unsigned binary number: ";
    if (!(std::cin >> binary) || binary < 0 || binary > 1111111111111111111LL) {
        std::cerr << "Enter at most 19 binary digits.\n";
        return 1;
    }
    unsigned int decimal = 0;
    unsigned int place = 1;
    while (binary > 0) {
        const int digit = static_cast<int>(binary % 10);
        if (digit != 0 && digit != 1) {
            std::cerr << "A binary digit must be 0 or 1.\n";
            return 1;
        }
        decimal += digit * place;
        place *= 2;
        binary /= 10;
    }
    std::cout << "The corresponding decimal number is " << decimal << '\n';
    return 0;
}
