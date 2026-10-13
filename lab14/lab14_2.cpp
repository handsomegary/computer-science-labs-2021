// Revised from the original 2021 Lab 14.2; use the required structure and both strings.
#include <iostream>
#include <string>

struct example {
    std::string str1;
    std::string str2;
};

int main() {
    example text;
    std::cout << "Please enter a string.\n";
    if (!std::getline(std::cin, text.str1)) return 0;
    std::cout << "str1 = " << text.str1 << '\n';
    text.str2 = text.str1;
    std::size_t digits = 0;
    for (std::size_t i = 0; i < text.str2.size(); ++i) {
        if (text.str2[i] >= '0' && text.str2[i] <= '9') {
            ++digits;
            text.str2[i] = '*';
        }
    }
    std::cout << "The number of the digits in the str1 is " << digits << ".\n"
              << "str2 = " << text.str2 << '\n';
    return 0;
}
