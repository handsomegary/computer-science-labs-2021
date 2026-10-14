#include <iostream>
#include <vector>

using namespace std;

void insertOp(long long int n, long long int sum, long long int require, long long int counter, long long int array[], long long int arraymemory[][50], long long int plusandmultiplication[][50]) {
    // long long int arraymemory[1 << n - 1][n] = { 0 };
    vector<vector<int> > aa(n - 1, vector<int>(1 << n - 1));
    unsigned num_to_fill = 1 << (n - 2);
    for (unsigned col = 0; col < n - 1; col++, num_to_fill >>= 1) {
        for (unsigned row = num_to_fill; row < (1 << n - 1); row += (num_to_fill * 2)) {
            fill_n(&aa[col][row], num_to_fill, 1);
        }
    }
    // long long int plusandmultiplication[1 << n - 1][n - 1];
    for (int i = 0; i < 1 << n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            plusandmultiplication[i][j] = aa[j][i];
        }
    }
    for (int i = 0;i < (1 << (n - 1));i++) {
        arraymemory[i][0] = array[0];
        for (int j = 0; j < n - 1;j++) {
            if (plusandmultiplication[i][j] == 0) {
                arraymemory[i][j + 1] = array[j + 1];
            }
            if (plusandmultiplication[i][j] == 1) {
                arraymemory[i][j + 1] = arraymemory[i][j] * array[j + 1];
                arraymemory[i][j] = 0;
            }
        }
    }
}

int main() {
    unsigned n;
    long long int array[100];
    long long int a, index = 0;
    while (cin >> a) {
        array[index++] = a;
        char ch = getchar();
        if (ch == '\n') {
            break;
        }
    }
    long long int require;
    long long int sum = 0;
    long long int counter = 0;
    cin >> require;
    n = index;
    long long int arraymemory[1 << n - 1][50] = { 0 };
    long long int plusandmultiplication[1 << n - 1][50];
    insertOp(n, sum, require, counter, array, arraymemory, plusandmultiplication);
    for (int i = 0;i < (1 << (n - 1));i++) {
        for (int j = 0; j < n;j++) {
            sum += arraymemory[i][j];
        }
        if (sum == require) {
            if (counter > 0) {
                cout << ", ";
            }
            cout << "[";
            for (int j = 0; j < n - 1;j++) {
                cout << array[j];
                if (plusandmultiplication[i][j] == 0) {
                    cout << " + ";
                }
                if (plusandmultiplication[i][j] == 1) {
                    cout << " * ";
                }
            }
            cout << array[n - 1];
            cout << "]";
            sum = 0;
            counter++;
        }
        else {
            sum = 0;
        }
    }
    if (counter == 0) {
        cout << "not found";
    }
    return 0;
}
