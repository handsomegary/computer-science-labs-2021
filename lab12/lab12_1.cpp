// Based on the original lab; count only successfully extracted scores.
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main() {
    string filename;
    cout << "Please enter the input file name:\n";
    if (!(cin >> filename)) return 0;
    ifstream infile(filename.c_str(), ios::in);
    if (!infile) { cout << "File could not be opened.\n"; return 0; }
    int score, students = 0, failed = 0;
    while (infile >> score) { ++students; if (score < 60) ++failed; }
    cout << students << '\n' << failed << '\n';
}
