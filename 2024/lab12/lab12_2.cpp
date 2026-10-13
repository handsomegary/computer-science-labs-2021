// 2024 Lab 12.2 / P113042: explicit pointer prototype from the written requirement.
#include <iostream>
using namespace std;
void digitalRoot(int num, int *dRoot) {
    // CODE BEGIN
    // Sum absolute digit remainders; unlike abs(num), this also handles INT_MIN.
    while (num != 0) {
        const int digit = num % 10;
        *dRoot += digit < 0 ? -digit : digit;
        num /= 10;
    }
    // CODE END
}
int main() {
    int num, dRoot;
    if (!(cin >> num)) return 0;
    do {
        dRoot = 0;
        digitalRoot(num, &dRoot);
        num = dRoot;
    } while (dRoot >= 10);
    cout << "digital root: " << dRoot << '\n';
    return 0;
}
