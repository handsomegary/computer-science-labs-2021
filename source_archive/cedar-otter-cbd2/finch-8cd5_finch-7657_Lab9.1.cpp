#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

int main() {
    string a;
    string b;
    cout << "Input Line1: ";
    getline(cin, a);
    cout << "Input Line2: ";
    getline(cin, b);
    int lengtha = a.length();
    int lengthb = b.length();
    vector <char> s1(lengtha);
    vector <char> s2(lengthb);
    for (int i = 0;i <= lengtha - 1; ++i) {
        s1[i] = a[lengtha - 1 - i];
        if (i == lengtha - 1) {
            s1[lengtha - 1] -= 32;
        }
    }
    for (int i = 1;i <= lengtha - 1; ++i) {
        if (s1[i] == 32) {
            s1[i - 1] -= 32;
        }
    }
    for (int i = 0;i <= lengthb - 1; ++i) {
        s2[i] = b[lengthb - 1 - i];
        if (i == lengthb - 1) {
            s2[lengthb - 1] -= 32;
        }
    }
    for (int i = 1;i <= lengthb - 1; ++i) {
        if (s2[i] == 32) {
            s2[i - 1] -= 32;
        }
    }
    cout << "Output Line: ";
    for (int k = lengtha - 1;k >= 0;k--) {
        cout << s1[k];
    }
    cout << " ";
    for (int k = lengthb - 1;k >= 0;k--) {
        cout << s2[k];
    }
}
