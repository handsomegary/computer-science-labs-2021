// 2024 Lab 11.2 / P113038: Gregorian calendar date, stored as character/digit arrays.
#include <iostream>
#include <string>
using namespace std;
int main() {
    string input;
    if (!(cin >> input)) return 0;
    char date[8];
    int date_int[8];
    bool legal = input.size() == 8;
    for (int i = 0; i < 8 && legal; ++i) {
        date[i] = input[i];
        if (date[i] < '0' || date[i] > '9') legal = false;
        else date_int[i] = date[i] - '0';
    }
    if (legal) {
        const int year = date_int[0] * 1000 + date_int[1] * 100 + date_int[2] * 10 + date_int[3];
        const int month = date_int[4] * 10 + date_int[5];
        const int day = date_int[6] * 10 + date_int[7];
        int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) days[1] = 29;
        legal = year >= 1 && month >= 1 && month <= 12 && day >= 1 && day <= days[month - 1];
    }
    cout << (legal ? "This is legal.\n" : "This is not legal.\n");
}
