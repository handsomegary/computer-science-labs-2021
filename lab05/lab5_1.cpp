#include <iostream>
#include <limits>

int main()
{
    long long size = 0;
    std::cout << "Enter the size of the diamond: ";
    while (true) {
        if (std::cin >> size) {
            if (size >= 3 && size <= 2147483647LL) {
                break;
            }
        } else {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Enter again: ";
    }

    // Review slide 6 defines rows = size / 2 + 1, including even input sizes.
    const long long rows = size / 2 + 1;
    for (long long row = 1; row <= rows; ++row) {
        for (long long star = 0; star <= rows - row; ++star) {
            std::cout << '*';
        }
        for (long long space = 1; space <= 2 * row - 1; ++space) {
            std::cout << ' ';
        }
        for (long long star = 0; star <= rows - row; ++star) {
            std::cout << '*';
        }
        std::cout << '\n';
    }
    for (long long row = rows - 1; row >= 1; --row) {
        for (long long star = 0; star <= rows - row; ++star) {
            std::cout << '*';
        }
        for (long long space = 1; space <= 2 * row - 1; ++space) {
            std::cout << ' ';
        }
        for (long long star = 0; star <= rows - row; ++star) {
            std::cout << '*';
        }
        std::cout << '\n';
    }
    return 0;
}
