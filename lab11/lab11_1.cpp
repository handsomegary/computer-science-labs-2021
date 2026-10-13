// Based on the original lab; corrected to the 2021 specification.
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

bool greater_than(int a, int b) { return a > b; }
bool less_than(int a, int b) { return a < b; }
void wave_sort(int *values, const int count, bool (*larger)(int, int),
               bool (*smaller)(int, int)) {
    for (int i = 0; i < count; ++i) {
        int selected = i;
        bool (*compare)(int, int) = i % 2 == 0 ? larger : smaller;
        for (int j = i + 1; j < count; ++j)
            if (compare(*(values + j), *(values + selected))) selected = j;
        const int temporary = *(values + i);
        *(values + i) = *(values + selected);
        *(values + selected) = temporary;
    }
}
int main() {
    string line;
    getline(cin, line);
    istringstream input(line);
    vector<int> values;
    int value;
    while (input >> value && values.size() < 20) values.push_back(value);
    if (!values.empty()) wave_sort(values.data(), static_cast<int>(values.size()),
                                   greater_than, less_than);
    for (size_t i = 0; i < values.size(); ++i) {
        if (i) cout << ' ';
        cout << values[i];
    }
    cout << '\n';
}
