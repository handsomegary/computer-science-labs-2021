// The Review omits the initial balance and menu numbering; see README.
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

bool readAmount(double& amount)
{
    while (true) {
        if (std::cin >> amount) {
            if (std::isfinite(amount) && amount > 0.0) {
                return true;
            }
        } else {
            if (std::cin.eof()) {
                return false;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Invalid amount. Enter again: ";
    }
}

int main()
{
    const int DEPOSIT = 1, WITHDRAW = 2, BORROW = 3, REPAY = 4, EXIT = 5;
    double balance = 0.0;
    double loanAmount = 0.0;
    const double interestRate = 0.05;
    std::cout << std::fixed << std::setprecision(2);
    while (true) {
        std::cout << "1. Deposit\n2. Withdraw\n3. Borrow\n4. Repay\n5. Exit\nEnter your selection: ";
        int choice = 0;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid selection.\n";
            continue;
        }
        double amount = 0.0;
        switch (choice) {
        case DEPOSIT:
            std::cout << "Enter the deposit amount: ";
            if (!readAmount(amount)) return 0;
            if (!std::isfinite(balance + amount)) {
                std::cout << "Amount is outside the supported numeric range.\n";
                break;
            }
            balance += amount;
            std::cout << "Current balance: $" << balance << '\n';
            break;
        case WITHDRAW:
            std::cout << "Enter the withdrawal amount: ";
            if (!readAmount(amount)) return 0;
            if (amount > balance) {
                std::cout << "Insufficient balance to withdraw.\n";
            } else {
                balance -= amount;
                std::cout << "Current balance: $" << balance << '\n';
            }
            break;
        case BORROW:
            // A single outstanding loan makes its duration unambiguous.
            if (loanAmount > 0.0) {
                std::cout << "Repay the outstanding loan before borrowing again.\n";
                break;
            }
            std::cout << "Enter the loan amount: ";
            if (!readAmount(amount)) return 0;
            if (!std::isfinite(balance + amount)) {
                std::cout << "Amount is outside the supported numeric range.\n";
                break;
            }
            loanAmount = amount;
            balance += amount;
            std::cout << "Current balance: $" << balance << '\n';
            break;
        case REPAY: {
            std::cout << "Current balance: $" << balance << '\n';
            if (loanAmount == 0.0) {
                std::cout << "No outstanding loan to repay.\n";
                break;
            }
            std::cout << "Enter the number of years since the loan: ";
            int years = 0;
            while (!(std::cin >> years) || years < 0) {
                if (std::cin.eof()) return 0;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid duration. Enter again: ";
            }
            const double totalRepay = loanAmount + loanAmount * interestRate * years;
            std::cout << "Total amount to repay: $" << totalRepay << '\n';
            if (balance >= totalRepay && std::isfinite(totalRepay)) {
                balance -= totalRepay;
                loanAmount = 0.0;
                std::cout << "Repayment successful.\nBalance after repayment: $" << balance << '\n';
            } else {
                std::cout << "Insufficient balance to repay the loan.\n";
            }
            break;
        }
        case EXIT:
            return 0;
        default:
            std::cout << "Invalid selection.\n";
            break;
        }
    }
}
