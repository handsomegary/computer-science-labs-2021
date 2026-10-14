#include <iostream>
using namespace std;

int gcd(int x, int y) {
    int a, b, r;
    if (x > y) {
        a = x;
        b = y;
    }
    else {
        a = y;
        b = x;
    }
    while (a != 0) {
        r = a;
        a = b % a;
        b = r;
    }
    return b;
}

int fact(int a) {
    int n;
    int c;

    n = 1;
    c = 1;

    while (n <= a) {
        c = c * n;
        n = n + 1;
    }
    return c;
}

int main() {
    long long int ain, bin, c_in;
    cout << "Enter 3 nums: ";
    cin >> ain >> bin >> c_in;
    ain = fact(ain);
    bin = fact(bin);
    c_in = fact(c_in);
    cout << "GCD of " << ain << " and " << bin << " and " << c_in << " is " << gcd(ain, gcd(bin, c_in));
    return 0;
}