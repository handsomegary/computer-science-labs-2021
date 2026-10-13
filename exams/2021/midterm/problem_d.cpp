// Based on the provided exam and reference code.
// Enumerate digit multisets rather than scanning the requested integer range.
#include <algorithm>
#include <iostream>
#include <vector>

bool matchingDigits(long long number, int length, const int counts[10])
{
    int actual[10] = {};
    int digits = 0;
    do {
        ++actual[number % 10];
        ++digits;
        number /= 10;
    } while (number > 0);
    if (digits != length) return false;
    for (int digit = 0; digit < 10; ++digit)
        if (actual[digit] != counts[digit]) return false;
    return true;
}

void enumerateDigits(int digit, int remaining, int length, long long sum,
                     const long long powers[10], int counts[10],
                     long long lower, long long upper, std::vector<long long>& answers)
{
    if (digit == 9) {
        counts[9] = remaining;
        const long long candidate = sum + remaining * powers[9];
        if (candidate >= lower && candidate <= upper && matchingDigits(candidate, length, counts))
            answers.push_back(candidate);
        return;
    }
    for (int count = 0; count <= remaining; ++count) {
        const long long nextSum = sum + count * powers[digit];
        if (nextSum > upper) break;
        counts[digit] = count;
        enumerateDigits(digit + 1, remaining - count, length, nextSum,
                        powers, counts, lower, upper, answers);
    }
}

int main()
{
    long long lower = 0, upper = 0;
    if (!(std::cin >> lower >> upper) || lower < 0 || upper < 0
        || lower > 2147483647LL || upper > 2147483647LL) {
        std::cerr << "Invalid range.\n";
        return 1;
    }
    std::vector<long long> answers;
    int maximumLength = 1;
    for (long long rest = upper; rest >= 10; rest /= 10) ++maximumLength;
    if (lower <= upper) {
        for (int length = 1; length <= maximumLength; ++length) {
            long long powers[10] = {};
            for (int digit = 0; digit < 10; ++digit) {
                powers[digit] = 1;
                for (int exponent = 0; exponent < length; ++exponent) powers[digit] *= digit;
            }
            int counts[10] = {};
            enumerateDigits(0, length, length, 0, powers, counts, lower, upper, answers);
        }
    }
    std::sort(answers.begin(), answers.end());
    answers.erase(std::unique(answers.begin(), answers.end()), answers.end());
    if (answers.empty()) {
        std::cout << "none\n";
    } else {
        for (std::size_t index = 0; index < answers.size(); ++index) {
            if (index != 0) std::cout << " & ";
            std::cout << answers[index];
        }
        std::cout << " \n"; // The exam sample includes a space after the last value.
    }
    return 0;
}
