#include <iostream>
#include <string>

using namespace std;

int main() {
    int first_colum, first_row, second_colum, second_row;
    int array1[10][10], array2[10][10];
    while (1) {
        cout << "Enter rows and columns for first matrix:" << endl;
        cin >> first_row >> first_colum;
        cout << "Enter rows and columns for second matrix:" << endl;
        cin >> second_row >> second_colum;
        if (first_colum != second_row) {
            cout << "Cannot multiply these two matrixes.";
            break;
        }
        cout << endl << "Enter matrix 1:" << endl;
        for (int i = 0; i < first_row;i++) {
            for (int j = 0;j < first_colum;j++) {
                cin >> *(*(array1 + i) + j);
            }
        }
        cout << endl << "Enter matrix 2:" << endl;
        for (int i = 0; i < second_row;i++) {
            for (int j = 0;j < second_colum;j++) {
                cin >> *(*(array2 + i) + j);
            }
        }
        int sum = 0;
        cout << endl << "Output Matrix:" << endl;
        for (int i = 0; i < first_row;i++) {
            for (int j = 0; j < second_colum;j++) {
                for (int time = 0; time < first_colum;time++) {
                    sum += *(*(array1 + i) + time) * *(*(array2 + time) + j);
                }
                cout << sum << " ";
                sum = 0;
            }
            cout << endl;
        }
        break;
        // for (int j = 0;j < first_row;j++) {
        //     for (int i = 0;i < second_colum;i++) {
        //         cout << arraysum[j][i] << " ";
        //     }
        //     cout << endl;
        // }
    }
}
