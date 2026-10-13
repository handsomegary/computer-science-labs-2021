// Based on the provided exam and reference code.
#include <iostream>

int main()
{
    long long heads = 0;
    long long legs = 0;
    while (std::cin >> heads >> legs) {
        if (heads == 0 && legs == 0) {
            std::cout << "Bye\n";
            return 0;
        }
        if (heads < 0 || heads > 2147483647LL || legs < 0 || legs > 2147483647LL) {
            std::cerr << "Invalid input.\n";
            return 1;
        }
        if (legs % 2 != 0 || legs < 2 * heads || legs > 4 * heads) {
            std::cout << "no\n";
        } else {
            const long long rabbits = (legs - 2 * heads) / 2;
            const long long chicks = heads - rabbits;
            std::cout << "Chick " << chicks << " Rabbit " << rabbits << '\n';
        }
    }
    return 0;
}
