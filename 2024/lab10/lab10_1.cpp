// 2024 Lab 10.1 / P113033: Modifying Score.
#include <iostream>
#include <vector>
using namespace std;

bool modifyScore(vector<int>& scores, int k) {
    if (k <= 0 || static_cast<size_t>(k) > scores.size()) return false;
    scores[k - 1] = scores[k - 1] <= 90 ? scores[k - 1] + 10 : 100;
    return true;
}
int main() {
    int n, k;
    if (!(cin >> n) || n < 0) return 0;
    vector<int> scores(n);
    for (int i = 0; i < n; ++i) if (!(cin >> scores[i])) return 0;
    if (!(cin >> k)) return 0;
    if (!modifyScore(scores, k)) { cout << "invalid student number.\n"; return 0; }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << scores[i];
    }
    cout << '\n';
}
