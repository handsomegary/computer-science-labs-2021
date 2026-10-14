#include <iostream>
#include <cmath>

using namespace std;

int main()

{
    int n;
    while (1) {
        cout << "Please enter a number for the column of the Pascal triangle:" << endl;
        cin >> n;
        long long int array[n + 1][n + 1] = { 0 };
        for (int k = 0; k <= n;k++) {
            for (int r = 0; r <= n; r++) {
                if (k == r || r == 1) {
                    array[k][r] = 1;
                }
            }
        }
        for (int i = 3; i <= n; i++) {
            for (int j = 2; j < n;j++) {
                array[i][j] = array[i - 1][j] + array[i - 1][j - 1];
            }
        }
        if (n == 0) {
            cout << endl;
            break;
        }
        cout << 1 << endl;
        for (int i = 1;i < n;i++) {
            for (int j = 0;j < i + 1;j++) {
                cout << array[i + 1][j + 1] << "  ";
            }
            cout << endl;
        }
        cout << endl;
    }
}