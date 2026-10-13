// 2021 final D: compare lowercase-letter multiplicities.
#include <iostream>
#include <string>
using namespace std;
int main() {
    string first, second;
    if (!(cin >> first >> second) || first.size() > 1000000 || second.size() > 1000000) {
        cout << "error\n";
        return 1;
    }
    int counts[26] = {};
    for (size_t i = 0; i < first.size(); ++i) {
        if (first[i] < 'a' || first[i] > 'z') { cout << "error\n"; return 1; }
        ++counts[first[i] - 'a'];
    }
    for (size_t i = 0; i < second.size(); ++i) {
        if (second[i] < 'a' || second[i] > 'z') { cout << "error\n"; return 1; }
        --counts[second[i] - 'a'];
    }
    bool anagram = true;
    for (int i = 0; i < 26; ++i) if (counts[i] != 0) anagram = false;
    cout << (anagram ? "Yes! It's anagram.\n" : "No! It is not anagram.\n");
}
