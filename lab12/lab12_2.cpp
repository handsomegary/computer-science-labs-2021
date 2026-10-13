// Based on the original lab and Lab12_2_sample.cpp.
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
using namespace std;
int main() {
    string infilename, outfilename;
    ifstream infile;
    do {
        cout << "Please enter the input file name:\n";
        if (!(cin >> infilename)) return 0;
        infile.clear();
        infile.open(infilename.c_str(), ios::in);
        if (!infile) cout << "File could not be opened.\n";
    } while (!infile);
    // Read row by row: the header is not a gift; incomplete final rows are ignored.
    map<int, string> gifts;
    string line, present;
    int number;
    while (getline(infile, line)) {
        istringstream row(line);
        if (row >> number >> present && gifts.size() < 50) gifts[number] = present;
    }
    if (gifts.empty()) { cout << "File contains no gifts.\n"; return 0; }
    cout << "Please choose a lucky number:\n";
    string token;
    while (true) {
        if (!(cin >> token)) return 0;
        istringstream selection(token);
        char extra;
        if (selection >> number && !(selection >> extra) && gifts.count(number)) break;
        cout << "Invalid input! Please enter again:\n";
    }
    const size_t extension = infilename.find_last_of('.');
    const size_t separator = infilename.find_last_of("/\\");
    outfilename = (extension != string::npos && (separator == string::npos || extension > separator)
                   ? infilename.substr(0, extension) : infilename) + "out.txt";
    ofstream outfile(outfilename.c_str(), ios::out);
    if (!outfile) { cout << "File could not be opened.\n"; return 0; }
    outfile << "Congratulations! Your Christmas present is " << gifts.find(number)->second;
    outfile.close();
    if (!outfile) { cout << "File could not be opened.\n"; return 0; }
    cout << "Okay! Your Christmas present has been saved to " << outfilename << '\n';
}
