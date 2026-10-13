#include <iostream>

int main()
{
    long long number = 0;
    if (!(std::cin >> number)) {
        std::cerr << "Invalid integer.\n";
        return 1;
    }
    if (number < 0 || (number > 0 && number % 10 == 0)) {
        std::cout << "NO\n";
        return 0;
    }
    // Reverse only half the digits so even LLONG_MAX cannot overflow.
    long long front = number;
    long long reversed = 0;
    while (front > reversed) {
        reversed = reversed * 10 + front % 10;
        front /= 10;
    }
    if (front == reversed || front == reversed / 10) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
