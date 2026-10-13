// 2024 P113031: array-based, manual lexicographic next permutation.
#include <iostream>
#include <memory>
#include <new>
using namespace std;

void swapElements(long long *values, long long a, long long b) {
    const long long temporary = values[a];
    values[a] = values[b];
    values[b] = temporary;
}
void reverseSuffix(long long *values, long long start, long long end) {
    while (start < end) swapElements(values, start++, end--);
}
bool nextPermutation(long long *values, long long size) {
    long long pivot = size - 2;
    while (pivot >= 0 && values[pivot] >= values[pivot + 1]) --pivot;
    if (pivot < 0) return false;
    long long successor = size - 1;
    while (values[successor] <= values[pivot]) --successor;
    swapElements(values, pivot, successor);
    reverseSuffix(values, pivot + 1, size - 1);
    return true;
}
int main() {
    long long size;
    if (!(cin >> size) || size < 1 || size > 2147483647LL) { cout << "error\n"; return 1; }
    unique_ptr<long long[]> values;
    try { values.reset(new long long[static_cast<size_t>(size)]); }
    catch (const bad_alloc &) { cout << "error\n"; return 1; }
    for (long long i = 0; i < size; ++i) if (!(cin >> values[static_cast<size_t>(i)])) return 1;
    // Start at the first permutation, so an unsorted input still emits all
    // permutations as required, instead of only its lexicographic suffix.
    for (long long i = 1; i < size; ++i) {
        const long long value = values[static_cast<size_t>(i)];
        long long j = i;
        while (j > 0 && values[static_cast<size_t>(j - 1)] > value) {
            values[static_cast<size_t>(j)] = values[static_cast<size_t>(j - 1)];
            --j;
        }
        values[static_cast<size_t>(j)] = value;
    }
    for (long long i = 1; i < size; ++i) {
        if (values[static_cast<size_t>(i - 1)] == values[static_cast<size_t>(i)]) {
            cout << "error\n";
            return 1;
        }
    }
    do {
        for (long long i = 0; i < size; ++i) {
            if (i) cout << ' ';
            cout << values[static_cast<size_t>(i)];
        }
        cout << '\n';
    } while (nextPermutation(values.get(), size));
}
