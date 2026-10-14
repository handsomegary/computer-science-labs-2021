#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

int main() {
    int input;
    int time;
    while (1) {
        cout << "Input dimension: ";
        cin >> input;
        if (input == -1) {
            cout << endl;
            break;
        }
        cout << endl;
        if (input % 2 == 0) {
            time = input / 2;
        }
        if (input % 2 == 1) {
            time = (input + 1) / 2;
        }
        int array[input + 1][input + 1] = { {1} };
        int num = 1;
        for (int k = 1;k < time + 1;k++) {
            for (int i = k - 1;i < input - k + 1;i++) {
                array[k - 1][i] = num++;
            }
            for (int i = k;i < input - k + 1;i++) {
                array[i][input - 1 - k + 1] = num++;
            }
            for (int i = input - k - 1;i > k - 2;i--) {
                array[input - k][i] = num++;
            }
            for (int i = input - k - 1;i > k - 1;i--) {
                array[i][k - 1] = num++;
            }
        }
        for (int k = 0;k < input;k++) {
            for (int i = 0;i < input;i++) {
                if (input < 4) {
                    cout << array[k][i] << " ";
                }
                if (input >= 4 && input < 10) {
                    if (array[k][i] < 10) {
                        cout << "0" << array[k][i] << " ";
                    }
                    else {
                        cout << array[k][i] << " ";
                    }
                }
                if (input >= 10 && input < 32) {
                    if (array[k][i] < 10) {
                        cout << "00" << array[k][i] << " ";
                    }
                    else if (array[k][i] >= 10 && array[k][i] < 100) {
                        cout << "0" << array[k][i] << " ";
                    }
                    else {
                        cout << array[k][i] << " ";
                    }
                }
            }
            cout << endl;
        }
        cout << endl;
    }
}