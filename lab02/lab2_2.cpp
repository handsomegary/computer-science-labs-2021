#include <iostream>

int main()
{
    int first = 0;
    int second = 0;
    int operation = 0;
    std::cout << "Please input 2 different integers: \n";
    if (!(std::cin >> first >> second)) {
        std::cerr << "Invalid integers.\n";
        return 1;
    }
    std::cout << "Please input the operation: \n";
    if (!(std::cin >> operation)) {
        std::cerr << "Invalid operation.\n";
        return 1;
    }

    // Promote before arithmetic: two 32-bit inputs can overflow an int result.
    if (operation == 1) {
        std::cout << "Summation is " << static_cast<long long>(first) + second;
    } else if (operation == 2) {
        std::cout << "Multiplication is " << static_cast<long long>(first) * second;
    } else if (operation == 3) {
        std::cout << "Larger number is " << (first > second ? first : second);
    } else if (operation == 4) {
        std::cout << "Smaller number is " << (first < second ? first : second);
    } else {
        std::cerr << "Operation must be between 1 and 4.\n";
        return 1;
    }
    std::cout << '\n';
    return 0;
}
