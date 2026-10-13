// Based on the original lab; corrected to the 2021 specification.
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void swap(long long *const left, long long *const right) {
    const long long temporary = *left;
    *left = *right;
    *right = temporary;
}
void reverse(long long *values, const int count) {
    for (int i = 0; i < count / 2; ++i)
        swap(values + i, values + count - i - 1);
}
int main() {
    string line;
    getline(cin, line);
    istringstream input(line);
    vector<long long> values;
    long long value;
    while (input >> value && values.size() < 50) values.push_back(value);
    if (!values.empty()) reverse(values.data(), static_cast<int>(values.size()));
    for (size_t i = 0; i < values.size(); ++i) {
        if (i) cout << ' ';
        cout << values[i];
    }
    cout << '\n';
}
