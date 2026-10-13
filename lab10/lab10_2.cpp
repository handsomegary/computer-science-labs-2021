// Based on the original lab; corrected to the 2021 specification.
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// A mountain consists of at least one strictly rising and one strictly falling edge.
// In a tie, retain the first mountain encountered from left to right.
void find_mountain(int *const num, int *const Length, const vector<long long>& values,
                   int *const start) {
    *num = *Length = *start = 0;
    size_t i = 0;
    while (i + 1 < values.size()) {
        const size_t begin = i;
        while (i + 1 < values.size() && values[i] < values[i + 1]) ++i;
        const size_t peak = i;
        while (i + 1 < values.size() && values[i] > values[i + 1]) ++i;
        if (peak > begin && i > peak) {
            ++*num;
            const int length = static_cast<int>(i - begin + 1);
            if (length > *Length) {
                *Length = length;
                *start = static_cast<int>(begin);
            }
        }
        if (i == begin) ++i;
    }
}
int main() {
    string line;
    getline(cin, line);
    istringstream input(line);
    vector<long long> values;
    long long value;
    while (input >> value && values.size() < 50) values.push_back(value);
    int count, length, start;
    find_mountain(&count, &length, values, &start);
    cout << count << '\n';
    for (int i = 0; i < length; ++i) {
        if (i) cout << ' ';
        cout << values[start + i];
    }
    cout << '\n';
}
