// Based on the unfinished original lab; completed for the 2021 specification.
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct SearchState {
    size_t next;
    unsigned long long sum, term;
    string expression;
};

// Find one next solution, keeping the explicit depth-first stack between calls.
// Saturation at target+1 is exact for finding a nonnegative target: a later *0
// still resets a saturated term to zero. Never discard that possibility.
void insertOp(const vector<unsigned long long>& values, unsigned long long target,
              vector<SearchState>& stack, string& result, bool *const found) {
    *found = false;
    const unsigned long long cap = target + 1;
    while (!stack.empty()) {
        SearchState current = stack.back();
        stack.pop_back();
        if (current.sum > target) continue;
        bool zero_ahead = false;
        for (size_t i = current.next; i < values.size(); ++i)
            if (values[i] == 0) zero_ahead = true;
        if (!zero_ahead && current.term > target - current.sum) continue;
        // A loose upper bound: even multiplying the entire partial sum cannot
        // underestimate a future expression. This also prunes all-zero suffixes.
        unsigned long long upper = current.term > target - current.sum ? cap : current.sum + current.term;
        for (size_t i = current.next; i < values.size() && upper < cap; ++i) {
            const unsigned long long addition = values[i] > cap - upper ? cap : upper + values[i];
            const unsigned long long multiplication = values[i] != 0 && upper > cap / values[i]
                                                        ? cap : upper * values[i];
            upper = addition > multiplication ? addition : multiplication;
        }
        if (upper < target) continue;
        if (current.next == values.size()) {
            if (current.term == target - current.sum) {
                result = current.expression;
                *found = true;
                return;
            }
            continue;
        }
        const unsigned long long value = values[current.next];
        unsigned long long product = 0;
        if (value != 0 && current.term != 0)
            product = current.term > cap / value ? cap : current.term * value;
        // LIFO: push multiplication first so '+' is visited before '*'.
        stack.push_back(SearchState{current.next + 1, current.sum, product,
                                   current.expression + " * " + to_string(value)});
        if (current.term <= target - current.sum)
            stack.push_back(SearchState{current.next + 1, current.sum + current.term,
                                       value > cap ? cap : value,
                                       current.expression + " + " + to_string(value)});
    }
}
int main() {
    string line;
    getline(cin, line);
    istringstream input(line);
    vector<unsigned long long> values;
    unsigned long long value, target;
    while (input >> value && values.size() < 50) values.push_back(value);
    if (!(cin >> target) || target > 9223372036854775807ULL || values.empty()) {
        cout << "not found\n";
        return 0;
    }
    vector<SearchState> stack;
    stack.push_back(SearchState{1, 0, values.front() > target ? target + 1 : values.front(),
                               to_string(values.front())});
    bool any = false, found;
    string result;
    do {
        insertOp(values, target, stack, result, &found);
        if (found) {
            if (any) cout << ", ";
            cout << '[' << result << ']';
            any = true;
        }
    } while (found);
    if (!any) cout << "not found";
    cout << '\n';
}
