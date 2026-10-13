// 2024 Lab 10.2 / P113034: Transpose Matrix.
#include <iostream>
using namespace std;

void transpose(const long long matrix[][100], long long result[][100], int n, int m) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) result[j][i] = matrix[i][j];
}
int main() {
    int n, m;
    if (!(cin >> n >> m) || n < 1 || n > 100 || m < 1 || m > 100) return 0;
    long long matrix[100][100], result[100][100];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) if (!(cin >> matrix[i][j])) return 0;
    transpose(matrix, result, n, m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) cout << ' ';
            cout << result[i][j];
        }
        cout << '\n';
    }
}
