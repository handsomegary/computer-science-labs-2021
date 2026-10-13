#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

bool readRate(double& rate, const char* company)
{
    while (true) {
        std::cout << "Enter the annual interest rate for " << company << " company: ";
        if (!(std::cin >> rate)) {
            if (std::cin.eof()) {
                return false;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Out of range, interest rate should be in the range [0.00, 1.00]\n";
            continue;
        }
        if (!std::isfinite(rate) || rate < 0.0 || rate > 1.0) {
            std::cout << "Out of range, interest rate should be in the range [0.00, 1.00]\n";
            continue;
        }
        break;
    }
    return true;
}

int main()
{
    double rateAndy = 0.0;
    double rateNCU = 0.0;
    double rateEE = 0.0;
    if (!readRate(rateAndy, "Andy") || !readRate(rateNCU, "NCU") || !readRate(rateEE, "EE")) {
        return 0;
    }
    std::cout << std::fixed << std::setprecision(2);
    while (true) {
        std::cout << "\n1. Andy company (" << rateAndy * 100 << "%)\n"
                  << "2. NCU company (" << rateNCU * 100 << "%)\n"
                  << "3. EE company (" << rateEE * 100 << "%)\n"
                  << "4. Exit this program\n"
                  << "Please select a company (1-3) or enter 4 to exit: ";
        int company = 0;
        if (!(std::cin >> company)) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid selection.\n";
            continue;
        }
        if (company == 4) {
            break;
        }
        if (company < 1 || company > 3) {
            std::cout << "Invalid selection.\n";
            continue;
        }
        const double rate = company == 1 ? rateAndy : (company == 2 ? rateNCU : rateEE);
        double monthlyInvestment = 0.0;
        std::cout << "Enter the monthly investment amount: ";
        if (!(std::cin >> monthlyInvestment) || !std::isfinite(monthlyInvestment)
            || monthlyInvestment < 0.0) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid investment amount.\n";
            continue;
        }
        double total = 0.0;
        std::cout << "Year   Amount on deposit\n";
        for (int year = 1; year <= 10; ++year) {
            total = (total + monthlyInvestment * 12) * (1.0 + rate);
            if (!std::isfinite(total)) {
                std::cerr << "Amount is outside the supported numeric range.\n";
                return 1;
            }
            std::cout << std::setw(4) << year << std::setw(21) << total << '\n';
        }
    }
    return 0;
}
