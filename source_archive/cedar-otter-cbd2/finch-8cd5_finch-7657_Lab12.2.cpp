#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string txt;
    string outfilename;
    int many = 0;
    int luckynumber;
    int whichpresents;
    string presents;
    string yourpresent;
    while (1) {
        cout << "Please enter the input file name:" << endl;
        cin >> txt;
        outfilename = txt.substr(0, txt.length() - 4) + "out.txt";
        ifstream inClientFile(txt, ios::in);
        if (!inClientFile) {
            cout << "File could not be opened." << endl;
            continue;
        }
        inClientFile >> presents >> presents;
        while (inClientFile >> whichpresents >> presents) {
            many++;
        }
        cout << "Please choose a lucky number:" << endl;
        while (1) {
            cin >> luckynumber;
            if (luckynumber > many) {
                cout << "Invalid input! Please enter again:" << endl;
                continue;
            }
            if (luckynumber <= many) {
                ifstream inClientFile(txt, ios::in);
                inClientFile >> presents >> presents;
                while (inClientFile >> whichpresents >> yourpresent) {
                    if (luckynumber == whichpresents) {
                        break;
                    }
                }
                ofstream outfile(outfilename, ios::out);
                outfile << "Congratulations!Your Christmas present is " << yourpresent;
                cout << "Okay! Your Christmas present has been saved to " << outfilename;
                break;
            }
        }
        break;
    }
}
