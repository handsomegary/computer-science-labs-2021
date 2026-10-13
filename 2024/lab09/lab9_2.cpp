// 2024 P113030: sum the inclusive range, after rounding each input to tenths.
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
using namespace std;

bool recoverInput() {
    if (cin.eof()) return false;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}
int main() {
    long long size;
    while (true) {
        cout << "Please enter the size of the array: ";
        if ((cin >> size) && size >= 1 && size <= 2147483647LL) break;
        if (!recoverInput()) return 0;
        cout << "Wrong Input! Please enter again:\n";
    }
    unique_ptr<long long[]> values;
    try { values.reset(new long long[static_cast<size_t>(size)]); }
    catch (const bad_alloc &) { cout << "error\n"; return 1; }
    while (true) {
        cout << "Please enter the elements of the array:\n";
        bool valid = true;
        for (long long i = 0; i < size; ++i) {
            long double value;
            if (!(cin >> value) || !isfinite(value) || value < -2147483648.0L || value > 2147483647.0L) {
                valid = false;
                break;
            }
            values[static_cast<size_t>(i)] = static_cast<long long>(round(value * 10));
        }
        if (valid) break;
        if (!recoverInput()) return 0;
        cout << "Wrong Input! Please enter again:\n";
    }
    long long start, end;
    while (true) {
        cout << "Please enter two integers, start and end, representing the selected index range: ";
        if ((cin >> start >> end) && start >= 0 && start <= end && end < size) break;
        if (!recoverInput()) return 0;
        cout << "Wrong Input! Please enter again:\n";
    }
    long long sum = 0;
    for (long long i = start; i <= end; ++i) {
        const long long value = values[static_cast<size_t>(i)];
        if ((value > 0 && sum > numeric_limits<long long>::max() - value) ||
            (value < 0 && sum < numeric_limits<long long>::min() - value)) {
            cout << "error\n";
            return 1;
        }
        sum += value;
    }
    const unsigned long long magnitude = sum < 0 ? static_cast<unsigned long long>(-(sum + 1)) + 1
                                                 : static_cast<unsigned long long>(sum);
    cout << "The sum of the values in the index range [" << start << ", " << end << "] is: ";
    if (sum < 0) cout << '-';
    cout << magnitude / 10 << '.' << magnitude % 10 << '\n';
}
