// Based on the provided exam and reference code.
#include <algorithm>
#include <iostream>

void printBinary(unsigned number)
{
    if (number >= 2) printBinary(number / 2);
    std::cout << number % 2;
}

int main()
{
    long long count = 0;
    while (std::cin >> count) {
        if (count < 0 || count > 2147483647LL) {
            std::cerr << "Invalid data count.\n";
            return 1;
        }
        // The description requires a positive count; an empty data set has no extrema.
        if (count == 0) {
            std::cout << "Input again!\n";
            continue;
        }
        long long minimum = 2147483647LL;
        long long maximum = 0;
        for (long long index = 0; index < count; ++index) {
            long long value = 0;
            if (!(std::cin >> value) || value < 0 || value > 2147483647LL) {
                std::cerr << "Invalid revenue data.\n";
                return 1;
            }
            minimum = std::min(minimum, value);
            maximum = std::max(maximum, value);
        }
        const long long sum = minimum + maximum;
        if (sum % 2 != 0) {
            std::cout << "Input again!\n";
            continue; // Read both the new count and a complete new set of values.
        }
        const unsigned average = static_cast<unsigned>(sum / 2);
        std::cout << "Decimal " << average << "\nOctet " << std::oct << average << std::dec << "\nBinary ";
        printBinary(average);
        std::cout << '\n' << (average >= 63 ? "The country is rich\n" : "Come on\n");
        return 0;
    }
    return 0;
}
