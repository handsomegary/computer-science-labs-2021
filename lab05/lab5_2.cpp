#include <iomanip>
#include <iostream>

int main()
{
    long long rows = 0;
    std::cout << "Enter number of rows: ";
    if (!(std::cin >> rows) || rows < 0 || rows > 2147483647LL) {
        std::cerr << "Rows must be between 0 and 2147483647.\n";
        return 1;
    }
    for (long long row = 1; row <= rows; ++row) {
        for (long long indent = 0; indent < rows - row; ++indent) {
            std::cout << "    ";
        }
        long long number = (row - 1) * (row - 1) + 1;
        for (long long column = 1; column <= 2 * row - 1; ++column) {
            // One separating space followed by a minimum three-column number.
            std::cout << ' ' << std::setw(3) << number;
            ++number;
        }
        std::cout << '\n';
    }
    return 0;
}
