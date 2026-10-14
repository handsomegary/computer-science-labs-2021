#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

int k = 0;
int w = 0;

int main() {
    string uhave;
    int counter = 0;
    cout << "Please enter the arithmetic: ";
    cin >> uhave;
    int array[100];
    char arra[100];
    int start = 0;
    string number;
    for (int i = 0; i < uhave.length(); i++) {
        if (uhave[i] < '0' || uhave[i]>'9') {
            number = uhave.substr(start, i - start);
            start = i + 1;
            array[k++] = stoi(number);
        }
        if (i == uhave.length() - 1) {
            number = uhave.substr(start, i + 1 - start);
            array[k++] = stoi(number);
        }
    }
    for (int i = 0;i < uhave.length();i++) {
        if (uhave[i] < 48 || uhave[i] > 57) {
            arra[w] = uhave[i];
            w++;
            if (uhave[i] == '*' || uhave[i] == '/' || uhave[i] == '%') {
                counter++;
            }
        }
    }
    for (int i = 0;i < w;i++) {
        if (arra[i] == '*') {
            array[i + 1] *= array[i];
            array[i] = 0;
            arra[i] = '+';
            counter--;
        }
        if (arra[i] == '/') {
            array[i + 1] = array[i] / array[i + 1];
            array[i] = 0;
            arra[i] = '+';
            counter--;
        }
        if (arra[i] == '%') {
            array[i + 1] = array[i] % array[i + 1];
            array[i] = 0;
            arra[i] = '+';
            counter--;
        }
    }
    // for (int i = 0;i < k;i++) {
    //     cout << array[i] << endl;
    // }
    for (int i = 0;i < w;i++) {
        if (arra[i] == '+') {
            for (int aa = i + 1;aa < k;aa++) {
                if (array[aa] != 0) {
                    array[0] += array[aa];
                    array[aa] = 0;
                    break;
                }
                else {
                    continue;
                }
            }
        }
        if (arra[i] == '-') {
            for (int aa = i + 1;aa < k;aa++) {
                if (array[aa] != 0) {
                    array[0] -= array[aa];
                    array[aa] = 0;
                    break;
                }
                else {
                    continue;
                }
            }
        }
    }
    cout << array[0];
}