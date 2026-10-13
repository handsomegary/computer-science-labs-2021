#include <iostream>

int main()
{
    int first = 0;
    int second = 0;
    int third = 0;
    std::cout << "Please enter 3 different integers: \n";
    if (!(std::cin >> first >> second >> third)) {
        std::cerr << "Invalid integers.\n";
        return 1;
    }
    // Three compare-and-swap steps sort all six orders without subtraction.
    int temporary = 0;
    if (first > second) {
        temporary = first;
        first = second;
        second = temporary;
    }
    if (second > third) {
        temporary = second;
        second = third;
        third = temporary;
    }
    if (first > second) {
        temporary = first;
        first = second;
        second = temporary;
    }
    std::cout << "The sorting result from small to large is "
              << first << "->" << second << "->" << third << '\n';
    return 0;
}
