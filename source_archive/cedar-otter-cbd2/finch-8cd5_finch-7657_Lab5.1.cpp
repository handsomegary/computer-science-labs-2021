#include <iostream>

using namespace std;

int main() {
    long long int x;
    long long int z = 0;
    long long int mz = z;
    cout << "Enter the size of the diamond: ";
    cin >> x;
    while (x <= 3) {
        cout << "Enter again: ";
        cin >> x;
    }

    for (long long int i = 0; i < x / 2 + 1; i++) {
        while (z < x / 2 + 1 - i) {
            cout << "*";
            z++;
        }
        z = mz;
        while (z < i * 2 + 1) {
            cout << " ";
            z++;
        }
        z = mz;
        while (z < x / 2 + 1 - i) {
            cout << "*";
            z++;
        }
        z = mz;
        cout << endl;
    }
    for (long long int i = 0; i < x / 2; i++) {
        while (z < 2 + i) {
            cout << "*";
            z++;
        }
        z = mz;
        while (z < x - 2 - i * 2) {
            cout << " ";
            z++;
        }
        z = mz;
        while (z < 2 + i) {
            cout << "*";
            z++;
        }
        z = mz;
        cout << endl;
    }
    return 0;
}