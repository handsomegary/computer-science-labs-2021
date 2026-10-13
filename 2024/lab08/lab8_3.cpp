// 2024 P1130293: count ordered subtraction paths for the three digit choices.
// Array memoization is permitted; no vector or string is used.
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>
using namespace std;

uint64_t remain(unsigned amount, unsigned a, unsigned b, unsigned c,
                uint64_t *memo, bool *known, bool *overflow) {
    if (amount == 0) return 1;
    if (known[amount]) return memo[amount];
    uint64_t total = 0;
    for (unsigned choice = 0; choice < 3; ++choice) {
        const unsigned step = choice == 0 ? a : choice == 1 ? b : c;
        if (step > amount) continue;
        const uint64_t count = remain(amount - step, a, b, c, memo, known, overflow);
        if (overflow[amount - step] || count > numeric_limits<uint64_t>::max() - total) {
            overflow[amount] = true;
            total = numeric_limits<uint64_t>::max();
        } else total += count;
    }
    known[amount] = true;
    memo[amount] = total;
    return total;
}

// Fill smaller amounts first via balanced recursion. remain() then recurses
// only into cached states, avoiding a call stack proportional to candy count.
void fillCounts(unsigned first, unsigned last, unsigned a, unsigned b, unsigned c,
                uint64_t *memo, bool *known, bool *overflow) {
    if (first > last) return;
    if (first == last) { remain(first, a, b, c, memo, known, overflow); return; }
    const unsigned middle = first + (last - first) / 2;
    fillCounts(first, middle, a, b, c, memo, known, overflow);
    fillCounts(middle + 1, last, a, b, c, memo, known, overflow);
}
int main() {
    int64_t amountInput, choicesInput;
    if (!(cin >> amountInput >> choicesInput) || amountInput < 0 ||
        static_cast<uint64_t>(amountInput) > numeric_limits<unsigned>::max() ||
        choicesInput < 100 || choicesInput > 999) {
        cout << "error\n";
        return 1;
    }
    const unsigned amount = static_cast<unsigned>(amountInput);
    const unsigned choices = static_cast<unsigned>(choicesInput);
    const unsigned a = choices / 100, b = choices / 10 % 10, c = choices % 10;
    if (a == 0 || b == 0 || c == 0) { cout << "error\n"; return 1; }
    try {
        if (static_cast<uint64_t>(amount) >= numeric_limits<size_t>::max()) {
            cout << "error\n";
            return 1;
        }
        const size_t size = static_cast<size_t>(amount) + 1;
        unique_ptr<uint64_t[]> memo(new uint64_t[size]());
        unique_ptr<bool[]> known(new bool[size]());
        unique_ptr<bool[]> overflow(new bool[size]());
        fillCounts(1, amount, a, b, c, memo.get(), known.get(), overflow.get());
        const uint64_t result = remain(amount, a, b, c, memo.get(), known.get(), overflow.get());
        if (overflow[amount]) throw overflow_error("count overflow");
        cout << result << '\n';
    } catch (const exception &) { cout << "error\n"; return 1; }
}
