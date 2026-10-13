#include <iostream>
#include <new>
#include <vector>
using namespace std;

// Manual merge sort: O(n log n), without a library sorting function.
void mergeSort(vector<long long> &numbers, vector<long long> &scratch, size_t begin, size_t end) {
    if (end - begin < 2) return;
    const size_t middle = begin + (end - begin) / 2;
    mergeSort(numbers, scratch, begin, middle);
    mergeSort(numbers, scratch, middle, end);
    size_t left = begin, right = middle, at = begin;
    while (left < middle && right < end) {
        if (numbers[left] <= numbers[right]) scratch[at++] = numbers[left++];
        else scratch[at++] = numbers[right++];
    }
    while (left < middle) scratch[at++] = numbers[left++];
    while (right < end) scratch[at++] = numbers[right++];
    for (size_t i = begin; i < end; ++i) numbers[i] = scratch[i];
}

int main() {
    long long n;
    cout << "Enter a number:\n";
    if (!(cin >> n) || n < 1 || n > 2147483647LL) {
        cout << "Invalid input\n";
        return 1;
    }
    vector<long long> numbers, scratch;
    try {
        numbers.resize(static_cast<size_t>(n));
        scratch.resize(static_cast<size_t>(n));
    }
    catch (const bad_alloc &) { cout << "Not enough memory\n"; return 1; }
    for (size_t i = 0; i < numbers.size(); ++i)
        if (!(cin >> numbers[i]) || numbers[i] < -2147483649LL || numbers[i] > 2147483647LL) return 1;
    mergeSort(numbers, scratch, 0, numbers.size());
    cout << "After sorting:\n";
    for (size_t i = 0; i < numbers.size(); ++i) cout << numbers[i] << ' ';
    long long median = numbers[numbers.size() / 2];
    if (numbers.size() % 2 == 0) {
        const long long sum = numbers[numbers.size() / 2 - 1] + numbers[numbers.size() / 2];
        median = sum / 2;
        if (sum < 0 && sum % 2) --median; // mathematical floor, not truncation
    }
    cout << "\nMedian value of this series is: " << median << '\n';
}
