// 2024 Lab 10.3 / P113035: Book Arrangement; stable ASCII case-insensitive order.
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

unsigned char folded(unsigned char letter) {
    return letter >= 'A' && letter <= 'Z' ? static_cast<unsigned char>(letter + ('a' - 'A')) : letter;
}
bool title_less(const vector<char>& left, const vector<char>& right) {
    size_t i = 0;
    while (i < left.size() && i < right.size()) {
        const unsigned char a = folded(static_cast<unsigned char>(left[i]));
        const unsigned char b = folded(static_cast<unsigned char>(right[i]));
        if (a != b) return a < b;
        ++i;
    }
    return left.size() < right.size();
}
int main() {
    int n;
    if (!(cin >> n) || n < 0) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<vector<char> > titles(n);
    string line;
    for (int i = 0; i < n; ++i) {
        if (!getline(cin, line)) return 0;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        titles[i].assign(line.begin(), line.end());
    }
    // Stable insertion sort keeps the original order of titles equal ignoring case.
    for (int i = 1; i < n; ++i) {
        vector<char> current = titles[i];
        int j = i;
        while (j > 0 && title_less(current, titles[j - 1])) {
            titles[j] = titles[j - 1];
            --j;
        }
        titles[j] = current;
    }
    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j < titles[i].size(); ++j) cout << titles[i][j];
        cout << '\n';
    }
}
