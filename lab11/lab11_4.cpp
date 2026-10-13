// Based on the original lab; use a sieve for the 10 ms algorithm target.
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cout << "Input number: ";
    if (!(cin >> n) || n < 4 || n > 50000) return 0;
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for (int p = 2; p * p <= n; ++p)
        if (prime[p])
            for (int multiple = p * p; multiple <= n; multiple += p) prime[multiple] = false;
    int count = 0;
    for (int p = 2; p <= n / 2; ++p)
        if (prime[p] && prime[n - p]) ++count;
    cout << "Number of combinations: " << count << '\n';
}
