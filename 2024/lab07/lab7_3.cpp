// 2024 P113027 Review reference implementation.
// The provided slides omit the original definition and output contract.
// Default: exactly two prime factors, counting multiplicity (semiprime).
// -DALMOST_PRIME_MODE=1: prime powers p^k, k>=2.
// -DALMOST_PRIME_MODE=2: exactly two distinct prime factors.
// No array, vector, or std::string is used.
#include <cstdint>
#include <iostream>
using namespace std;

#ifndef ALMOST_PRIME_MODE
#define ALMOST_PRIME_MODE 0
#endif
static_assert(ALMOST_PRIME_MODE >= 0 && ALMOST_PRIME_MODE <= 2, "mode must be 0, 1, or 2");

bool almostPrime(uint64_t number) {
    if (number < 4) return false;
    unsigned multiplicity = 0, distinct = 0;
    for (uint64_t divisor = 2; divisor <= number / divisor; divisor += divisor == 2 ? 1 : 2) {
        if (number % divisor != 0) continue;
        ++distinct;
        do { number /= divisor; ++multiplicity; } while (number % divisor == 0);
        if (ALMOST_PRIME_MODE == 0 && multiplicity > 2) return false;
        if (ALMOST_PRIME_MODE == 1 && distinct > 1) return false;
        if (ALMOST_PRIME_MODE == 2 && distinct > 2) return false;
    }
    if (number > 1) { ++multiplicity; ++distinct; }
    if (ALMOST_PRIME_MODE == 1) return distinct == 1 && multiplicity >= 2;
    if (ALMOST_PRIME_MODE == 2) return distinct == 2;
    return multiplicity == 2;
}
uint64_t countAlmostPrimes(uint64_t lower, uint64_t upper) {
    uint64_t count = 0;
    if (lower > upper) return 0;
    for (uint64_t number = lower; ; ++number) {
        if (almostPrime(number)) ++count;
        if (number == upper) break;
    }
    return count;
}
void printBase(uint64_t number, unsigned base) {
    if (number >= base) printBase(number / base, base);
    const unsigned digit = static_cast<unsigned>(number % base);
    cout << static_cast<char>(digit < 10 ? '0' + digit : 'A' + digit - 10);
}
int main() {
    int64_t lowerInput, upperInput;
    if (!(cin >> lowerInput >> upperInput) || lowerInput < 0 || upperInput < lowerInput) return 1;
    const uint64_t lower = static_cast<uint64_t>(lowerInput);
    const uint64_t upper = static_cast<uint64_t>(upperInput);
    const uint64_t count = countAlmostPrimes(lower, upper);
    cout << "decimal: " << count << "\nbinary: ";
    printBase(count, 2);
    cout << "\nhex: ";
    printBase(count, 16);
    cout << '\n';
}
