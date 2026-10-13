// 2024 P1130294: recursive score rules reproduced from the calculate() hint.
// Neither vector nor string is used.
#include <cstdint>
#include <iostream>
using namespace std;

uint64_t power10(unsigned place) {
    uint64_t result = 1;
    for (unsigned i = 0; i < place; ++i) result *= 10;
    return result;
}
unsigned digitAt(uint64_t number, int place) {
    return static_cast<unsigned>(number / power10(static_cast<unsigned>(place)) % 10);
}
bool allOnes(uint64_t number, int left, int right) {
    if (left < right) return true;
    return digitAt(number, left) == 1 && allOnes(number, left - 1, right);
}
uint64_t calculate(uint64_t number, int left, int right) {
    if (left <= right) return 0;
    if (left - right == 1 && digitAt(number, left) == 1 && digitAt(number, right) == 2) return 1;
    int symmetry = 0;
    for (int i = left; i > right; --i) {
        if (digitAt(number, i) == 1) ++symmetry;
        else if (digitAt(number, i) == 2) --symmetry;
        if (symmetry == 0 || symmetry == -1)
            return calculate(number, left, i) + calculate(number, i - 1, right);
    }
    if (digitAt(number, left) == 1 && digitAt(number, right) == 2) {
        if (allOnes(number, left - 1, right + 1)) return 1;
        return calculate(number, left - 1, right + 1) * 5;
    }
    return calculate(number, left, right + 1);
}
int main() {
    int64_t input;
    if (!(cin >> input) || input < 0) return 1;
    const uint64_t number = static_cast<uint64_t>(input);
    int highest = 0;
    for (uint64_t rest = number; rest >= 10; rest /= 10) ++highest;
    cout << calculate(number, highest, 0) << '\n';
}
