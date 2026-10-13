// 2024 Lab 11.1 / P113037 (mislabelled Lab 1.1 in the supplied slides).
#include <iomanip>
#include <iostream>
using namespace std;
int main() {
    double price, discount;
    double *pricePtr = 0;
    cout << "Please enter the price: ";
    if (!(cin >> price)) return 0;
    cout << "Please enter the discount: ";
    if (!(cin >> discount)) return 0;
    // CODE BEGIN
    pricePtr = &price;
    *pricePtr *= discount;
    // CODE END
    cout << fixed << setprecision(2) << "After discount, the price is " << *pricePtr << '\n';
}
