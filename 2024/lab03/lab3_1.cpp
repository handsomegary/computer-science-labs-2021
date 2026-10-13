// 2024 Lab 3.1: the Review does not provide an initial total-candy prompt.
#include <iostream>
#include <limits>

int main()
{
    long long remaining = 0;
    if (!(std::cin >> remaining) || remaining < 0) {
        std::cerr << "The total candy count must be nonnegative.\n";
        return 1;
    }
    while (remaining > 0) {
        std::cout << "The candy bar is open!\n";
        std::cout << "How many candy do you want to take: ";
        long long taken = 0;
        while (!(std::cin >> taken) || taken < 0) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid candy count. Enter again: ";
        }
        // Taking at least the remaining amount empties the bar without overflow.
        if (taken >= remaining) {
            remaining = 0;
        } else {
            remaining -= taken;
        }
    }
    std::cout << "The candy bar is closed!\n";
    return 0;
}
