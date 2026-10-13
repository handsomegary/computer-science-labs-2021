// 2024 P113026: a lamp remains on precisely at a perfect-square index.
#include <cstdint>
#include <iostream>
using namespace std;

bool isPerfectSquare(uint64_t number) {
    if (number == 0) return true;
    uint64_t low = 1, high = number < 3037000499ULL ? number : 3037000499ULL;
    while (low <= high) {
        const uint64_t middle = low + (high - low) / 2;
        const uint64_t quotient = number / middle;
        if (middle == quotient && number % middle == 0) return true;
        if (middle > quotient) high = middle - 1;
        else low = middle + 1;
    }
    return false;
}
int main() {
    int64_t input;
    if (!(cin >> input) || input < 0) return 1;
    const uint64_t number = static_cast<uint64_t>(input);
    cout << (isPerfectSquare(number) ? "on" : "off") << '\n';
}
