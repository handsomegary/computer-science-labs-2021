// 2024 P113022: int return type is retained; overflow is reported explicitly.
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

int LCM_calculator(int a, int b) {
    if (a <= 0 || b <= 0) throw invalid_argument("positive integers required");
    int x = a, y = b;
    while (y) { const int remainder = x % y; x = y; y = remainder; }
    const long long lcm = static_cast<long long>(a / x) * b;
    if (lcm > numeric_limits<int>::max()) throw overflow_error("LCM exceeds int");
    return static_cast<int>(lcm);
}
int main() {
    int a, b;
    if (!(cin >> a >> b)) { cout << "error\n"; return 1; }
    try { cout << LCM_calculator(a, b) << '\n'; }
    catch (const exception &) { cout << "error\n"; return 1; }
}
