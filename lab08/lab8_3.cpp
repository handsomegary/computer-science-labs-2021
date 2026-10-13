#include <iostream>
#include <limits>
using namespace std;

int main() {
    int n;
    int triangle[30][30] = {};
    while (true) {
        cout << "Please enter a number for the column of the Pascal triangle:\n";
        if (!(cin >> n)) {
            if (cin.eof()) return 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            continue;
        }
        if (n == 0) return 0;
        if (n < 1 || n > 30) {
            cout << "Invalid input\n";
            continue;
        }
        for (int row = 0; row < n; ++row) {
            triangle[row][0] = triangle[row][row] = 1;
            for (int col = 1; col < row; ++col)
                triangle[row][col] = triangle[row - 1][col - 1] + triangle[row - 1][col];
            for (int col = 0; col <= row; ++col) {
                if (col) cout << "  ";
                cout << triangle[row][col];
            }
            cout << '\n';
        }
    }
}
