#include <iostream>
#include <limits>

int main()
{
    long long total = 0;
    long long first = 0, second = 0, third = 0;
    std::cout << "Enter the total number of the cookies: ";
    if (!(std::cin >> total) || total < 0) {
        std::cerr << "The total cookie count must be nonnegative.\n";
        return 1;
    }
    bool valid = false;
    do {
        std::cout << "Enter 3 different quantities: ";
        if (std::cin >> first >> second >> third) {
            valid = first >= 1 && first <= 10 && second >= 1 && second <= 10
                    && third >= 1 && third <= 10
                    && first != second && second != third && first != third;
        } else {
            if (std::cin.eof()) return 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (!valid) {
            std::cout << "Wrong quantities. Enter three quantities again.\n";
        }
    } while (!valid);
    long long temporary = 0;
    if (first > second) { temporary = first; first = second; second = temporary; }
    if (second > third) { temporary = second; second = third; third = temporary; }
    if (first > second) { temporary = first; first = second; second = temporary; }

    std::cout << "\nAll possibilities:\n";
    bool possible = false;
    const long long maximumFirst = total / first;
    for (long long dayFirst = 0; dayFirst <= maximumFirst; ++dayFirst) {
        const long long rest = total - dayFirst * first;
        for (long long daySecond = 0; daySecond <= rest / second; ++daySecond) {
            const long long remaining = rest - daySecond * second;
            if (remaining % third != 0) continue;
            const long long dayThird = remaining / third;
            possible = true;
            bool separator = false;
            std::cout << '[';
            for (long long day = 0; day < dayFirst; ++day) {
                if (separator) std::cout << ',';
                std::cout << first;
                separator = true;
            }
            for (long long day = 0; day < daySecond; ++day) {
                if (separator) std::cout << ',';
                std::cout << second;
                separator = true;
            }
            for (long long day = 0; day < dayThird; ++day) {
                if (separator) std::cout << ',';
                std::cout << third;
                separator = true;
            }
            std::cout << "]\n";
        }
        // Avoid an increment past LLONG_MAX for an enormous declared total.
        if (dayFirst == maximumFirst) break;
    }
    if (!possible) std::cout << "There is no way to finish the cookies.\n";
    return 0;
}
