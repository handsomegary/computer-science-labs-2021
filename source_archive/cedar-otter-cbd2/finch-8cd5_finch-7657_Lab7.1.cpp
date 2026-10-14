#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

long double my_sqrt(long long int k, long double low, long  double high) {

    if ((low + high) / 2 * (low + high) / 2 > k) {
        if ((low + high) / 2 * (low + high) / 2 - k < 1e-18) {
            return (low + high) / 2;
        }
        high = (low + high) / 2;
        return my_sqrt(k, low, high);
    }
    if ((low + high) / 2 * (low + high) / 2 == k) {
        return (low + high) / 2;
    }
    if ((low + high) / 2 * (low + high) / 2 < k) {
        if (-((low + high) / 2 * (low + high) / 2 - k) < 1e-18) {
            return (low + high) / 2;
        }
        low = (low + high) / 2;
        return my_sqrt(k, low, high);
    }
}

int main() {

    long long int b;
    cout << "Enter a number: ";
    cin >> b;
    while (b < 0) {
        cout << "The number is out of range. Please enter again: ";
        cin >> b;
    }
    if (b == 0) {
        cout << setprecision(10) << fixed << my_sqrt(b, 0, b);
    }
    else
        cout << setprecision(10) << fixed << (my_sqrt(b, 0, b) - 5e-11);
    return 0;
}

