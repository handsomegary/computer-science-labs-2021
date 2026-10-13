#include <iostream>

int main()
{
    int number = 0;
    std::cout << "Please enter a nonnegative integer: ";
    if (!(std::cin >> number) || number < 0 || number > 20) {
        std::cerr << "The integer must be between 0 and 20.\n";
        return 1;
    }
    unsigned long long factorial = 1;
    for (int factor = 2; factor <= number; ++factor) {
        factorial *= factor;
    }
    std::cout << "The corresponding factorial is " << factorial << '\n';
    return 0;
}
