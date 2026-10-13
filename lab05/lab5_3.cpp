#include <iomanip>
#include <iostream>
#include <limits>

int main()
{
    while (true) {
        int a = 0;
        int b = 0;
        int carryIn = 0;
        std::cout << "Enter a: ";
        if (!(std::cin >> a)) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "!!! Enter the inputs again !!!\n";
            continue;
        }
        if (a == -1) {
            std::cout << "Bye~\n";
            return 0;
        }
        std::cout << "Enter b: ";
        if (!(std::cin >> b)) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "!!! Enter the inputs again !!!\n";
            continue;
        }
        std::cout << "Enter Cin: ";
        if (!(std::cin >> carryIn)) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "!!! Enter the inputs again !!!\n";
            continue;
        }
        if ((a != 0 && a != 1) || (b != 0 && b != 1)
            || (carryIn != 0 && carryIn != 1)) {
            std::cout << "!!! Enter the inputs again !!!\n";
            continue;
        }

        // Odd parity is the sum; any pair of asserted inputs generates carry.
        const bool sum = (!a && !b && carryIn) || (!a && b && !carryIn)
                         || (a && !b && !carryIn) || (a && b && carryIn);
        const bool carryOut = (a && b) || (a && carryIn) || (b && carryIn);
        std::cout << "--------------------\n";
        std::cout << std::setw(3) << "A" << std::setw(3) << "B"
                  << std::setw(5) << "Cin" << std::setw(5) << "Sum"
                  << std::setw(4) << "Cout" << '\n';
        std::cout << std::setw(3) << a << std::setw(3) << b
                  << std::setw(5) << carryIn << std::setw(4) << sum
                  << std::setw(5) << carryOut << '\n';
        std::cout << "--------------------\n";
    }
}
