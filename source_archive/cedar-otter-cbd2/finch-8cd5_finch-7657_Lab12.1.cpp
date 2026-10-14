#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    cout << "Please enter the input file name:" << endl;
    string txt;
    cin >> txt;
    ifstream inClientFile(txt, ios::in);
    if (!inClientFile) {
        cout << "File could not be opened." << endl;
        exit(0);
    }
    int score;
    int many = 0;
    int failed = 0;
    while (inClientFile >> score) {
        many++;
        if (score < 60) {
            failed++;
        }
    }
    cout << many << endl << failed;
}