#include <cmath>
#include <iomanip>
#include <iostream>

int main()
{
    double annualInvestment = 0.0;
    double annualRate = 0.0;
    std::cout << "Enter the annual investment amount: ";
    if (!(std::cin >> annualInvestment) || !std::isfinite(annualInvestment)
        || annualInvestment < 0.0) {
        std::cerr << "Invalid investment amount.\n";
        return 1;
    }
    std::cout << "Enter the annual interest rate (as a decimal, e.g., 0.05 for 5%): ";
    if (!(std::cin >> annualRate) || !std::isfinite(annualRate) || annualRate < 0.0) {
        std::cerr << "Invalid interest rate.\n";
        return 1;
    }
    double totalAmount = 0.0;
    std::cout << "Year   Amount on deposit\n" << std::fixed << std::setprecision(2);
    for (int year = 1; year <= 10; ++year) {
        totalAmount = (totalAmount + annualInvestment) * (1.0 + annualRate);
        if (!std::isfinite(totalAmount)) {
            std::cerr << "Amount is outside the supported numeric range.\n";
            return 1;
        }
        std::cout << std::setw(4) << year << std::setw(21) << totalAmount << '\n';
    }
    return 0;
}
