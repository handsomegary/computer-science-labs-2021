#include <iostream>
#include <cmath>

using namespace std;

int main() {
    long long int array[3];
    cout << "Please enter the first term(a1), the common difference(d) and the number of terms(n):" << endl;
    cin >> array[0] >> array[1] >> array[2];
    cout << "The arithmetical series: ";
    for (int y = 0;y < array[2];y++) {
        if (y == array[2] - 1) {
            if (array[0] + array[1] * y < 0) {
                cout << "(" << array[0] + array[1] * y << ")" << " = ";
                if ((2 * array[0] + (array[2] - 1) * array[1]) * array[2] / 2 < 0) {
                    cout << "(" << (2 * array[0] + (array[2] - 1) * array[1]) * array[2] / 2 << ")";
                }
                else {
                    cout << (2 * array[0] + (array[2] - 1) * array[1]) * array[2] / 2;
                }
                break;
            }
            else {
                cout << array[0] + array[1] * y << " = " << (2 * array[0] + (array[2] - 1) * array[1]) * array[2] / 2;
                break;
            }
        }
        if (array[0] + array[1] * y < 0) {
            cout << "(" << array[0] + array[1] * y << ")" << " + ";
            continue;
        }
        cout << array[0] + array[1] * y << " + ";
    }
}