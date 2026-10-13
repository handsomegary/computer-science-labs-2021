// 2024 P113023: prompts and coupon brackets are transcribed from the slides.
#include <iostream>
#include <limits>
#include <string>
using namespace std;

bool enterStore() {
    string choice;
    cout << "*** NCU Electrical Appliance Store ***\n"
         << "Do you want to go inside or leave the store(Y/N): ";
    while (cin >> choice) {
        if (choice == "Y" || choice == "y") return true;
        if (choice == "N" || choice == "n") return false;
        cout << "Invalid input, please enter Y or N: ";
    }
    return false;
}
bool hasMembershipCard() {
    string choice;
    cout << "Do you have the membership card(Y/N): ";
    while (cin >> choice) {
        if (choice == "Y" || choice == "y") return true;
        if (choice == "N" || choice == "n") return false;
        cout << "Invalid input, please enter Y or N: ";
    }
    return false;
}
void calculateRewards(bool hasMembership, int spending) {
    if (hasMembership) {
        if (spending < 5000)
            cout << "***Congratulations !! You get 500 dollars coupon!!\n";
        else if (spending <= 10000)
            cout << "***Congratulations !! You get 1000 dollars coupon!!\n";
        else
            cout << "***Congratulations !! You get 3000 dollars coupon and one lottery ticket!!\n";
    } else {
        if (spending < 7000)
            cout << "***Oh no!! You do not have any bonus to get...\n";
        else if (spending <= 10000)
            cout << "***Congratulations !! You get 500 dollars coupon!!\n";
        else
            cout << "***Congratulations !! You get 1500 dollars coupon and become a store member!!\n";
    }
}
int main() {
    while (true) {
        if (!enterStore()) {
            if (cin) cout << "************************ GOOD BYE! *************************\n";
            return 0;
        }
        const bool member = hasMembershipCard();
        if (!cin) return 0;
        int spending;
        cout << "Enter the money you spent: ";
        while (true) {
            if (cin >> spending) {
                if (spending >= 0) break;
            } else {
                if (cin.eof()) return 0;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Invalid spending, please enter again: ";
        }
        calculateRewards(member, spending);
    }
}
