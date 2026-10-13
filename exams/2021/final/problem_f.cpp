// 2021 final F: infer N from all scores up to EOF; round to two decimal places.
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main() {
    cout << "Please enter the scores of all students:\n";
    int scores[50], count = 0, sum = 0;
    string token;
    while (cin >> token) {
        istringstream parser(token);
        int score;
        if (!(parser >> score) || parser.peek() != char_traits<char>::eof() ||
            score < 0 || score > 100 || count == 50) { cout << "error\n"; return 1; }
        scores[count++] = score;
        sum += score;
    }
    if (!cin.eof() || count == 0) { cout << "error\n"; return 1; }
    const int rounded = (sum * 100 + count / 2) / count;
    const int fraction = rounded % 100;
    cout << "avg = " << rounded / 100;
    if (fraction) {
        cout << '.';
        if (fraction % 10 == 0) cout << fraction / 10;
        else cout << setfill('0') << setw(2) << fraction;
    }
    cout << '\n';
    bool failed = false;
    for (int i = 0; i < count; ++i) if (scores[i] < 70) failed = true;
    if (failed) {
        cout << "fail:\n";
        for (int i = 0; i < count; ++i) if (scores[i] < 70) cout << i + 1 << ": " << scores[i] << '\n';
    }
}
