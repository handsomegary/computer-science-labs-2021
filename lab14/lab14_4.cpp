// Revised from the original 2021 Lab 14.4; retain the handout's required class API.
#include <iostream>
#include <string>

class reverse_str {
public:
    void set_string(std::string);
    void print_string();
    void reverse_string();
private:
    std::string str0;
};

void reverse_str::set_string(std::string input) { str0 = input; }
void reverse_str::print_string() { std::cout << str0 << '\n'; }
void reverse_str::reverse_string() {
    // Half-open bounds also handle an empty string without underflow.
    for (std::size_t left = 0, right = str0.size(); left < right; ++left) {
        --right;
        const char temp = str0[left];
        str0[left] = str0[right];
        str0[right] = temp;
    }
}

int main() {
    std::cout << "Please enter a string:\n";
    std::string input;
    if (!std::getline(std::cin, input)) return 0;
    reverse_str text;
    text.set_string(input);
    text.reverse_string();
    std::cout << "\nAfter reversed, the string is:\n";
    text.print_string();
    return 0;
}
