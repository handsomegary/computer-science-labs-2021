// Based on the supplied Lab 6.1 debugging template; its algorithm is preserved.
#include <cstdint>
#include <iostream>
using namespace std;

uint64_t gcd(uint64_t x, uint64_t y) {
    uint64_t a, b, r;                 // fix: declare all three variables
    if (x > y) {
        a = x;
        b = y;
    } else {
        a = y;
        b = x;
    }
    while (b != 0) {
        r = a % b;                    // fix: Euclidean remainder
        a = b;
        b = r;
    }
    return a;
}

uint64_t fact(uint64_t a) {
    uint64_t n;
    uint64_t c;
    n = 1;                            // fix: factorial begins at one
    c = 1;                            // fix: multiplicative identity
    while (n <= a) {
        c = c * n;
        n = n + 1;
    }
    return c;
}

int main() {
    uint64_t ain = 6, bin = 12, din = 9; // fix: avoid shadowing std::cin
    cout << "Enter 3 nums: ";
    if (!(cin >> ain >> bin >> din)) return 1;
    // 21! exceeds uint64_t. Report this instead of wrapping the result.
    if (ain < 1 || bin < 1 || din < 1 || ain > 20 || bin > 20 || din > 20) {
        cout << "Input out of range for 64-bit factorial (1-20).\n";
        return 1;
    }
    ain = fact(ain);
    bin = fact(bin);
    din = fact(din);
    cout << "GCD of " << ain << " and " << bin << " and " << din
         << " is " << gcd(ain, gcd(bin, din)) << '\n';
    return 0;
}
