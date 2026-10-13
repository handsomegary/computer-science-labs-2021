#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    int score[3], sum = 0;
    bool failed = false;
    cout << "Please enter the scores of three students:\n";
    for (int i = 0; i < 3; ++i) {
        if (!(cin >> score[i]) || score[i] < 0 || score[i] > 100) {
            cout << "Invalid score\n";
            return 1;
        }
        sum += score[i];
        if (score[i] < 60) failed = true;
    }
    cout << "avg = " << fixed << setprecision(3) << sum / 3.0 << '\n';
    if (failed) {
        cout << "fail:\n";
        for (int i = 0; i < 3; ++i)
            if (score[i] < 60) cout << i + 1 << ": " << score[i] << '\n';
    }
}
