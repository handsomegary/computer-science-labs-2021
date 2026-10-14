#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
int counter = 0;
int main() {
    string infilename;
    string aas;
    string arithmetic;
    string snumber;
    char ass;
    int input;
    int number[400];
    int profit = 0;
    int start = 0, digitNumber = 0;
    cout << "File: ";
    cin >> infilename;
    ifstream InGiftExchange(infilename, ios::in);
    InGiftExchange >> aas >> ass >> ass >> ass >> ass >> ass >> ass >> ass;
    while (InGiftExchange >> arithmetic) {
        int length = arithmetic.length();
        for (int i = 0; i < length; i++) {
            if (arithmetic[i] < '0' || arithmetic[i]>'9') {
                snumber = arithmetic.substr(start, i - start);
                start = i + 1;
                number[digitNumber++] = stoi(snumber);
            }
            if (i == length - 1) {
                snumber = arithmetic.substr(start, i + 1 - start);
                number[digitNumber++] = stoi(snumber);
            }
        }
    }
    for (int i = 0; i < digitNumber; i++) {
        if (number[i] < number[i + 1]) {
            profit += (number[i + 1] - number[i]);
        }
    }

    cout << "Maximum profit: " << profit;

}



