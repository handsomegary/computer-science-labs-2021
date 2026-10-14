#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void thecoolthing(char array[], string require, int whichone, int controlofthetruefalse, int& answer) {
    if (controlofthetruefalse == require.length()) {
        answer = 1;
    }
    else {
        int counterone = 0;
        if (require[controlofthetruefalse] == array[whichone - 9]) {
            thecoolthing(array, require, whichone - 9, controlofthetruefalse + 1, answer);
        }
        if (require[controlofthetruefalse] == array[whichone + 9]) {
            thecoolthing(array, require, whichone + 9, controlofthetruefalse + 1, answer);
        }
        int memory = whichone - 1;
        for (;counterone < 2;memory += 2, counterone++) {
            if (require[controlofthetruefalse] == array[memory]) {
                thecoolthing(array, require, memory, controlofthetruefalse + 1, answer);
            }
        }

    }
}
int main() {
    string require;
    ifstream infile;
    int controlofthetruefalse = 1;
    int answer = 0;
    infile.open("4_1.txt", ios::in);
    char array[81];
    char input;
    for (int i = 0;i < 81;i++) {
        infile >> input;
        array[i] = input;
    }
    while (cin >> require) {
        if (require == "-1") {
            break;
        }
        for (int i = 0;i < 81;i++) {
            if (array[i] == require[0]) {
                thecoolthing(array, require, i, controlofthetruefalse, answer);
            }
        }
        if (answer == 1) {
            cout << "True" << endl;
        }
        else {
            cout << "False" << endl;
        }
        answer = 0;
    }
}
