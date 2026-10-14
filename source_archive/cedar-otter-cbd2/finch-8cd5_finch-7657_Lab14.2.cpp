#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int counter = 0;

struct example {
    string str1;
    string str2;
};

int main() {
    example adad;
    cout << "Please enter a string." << endl;
    getline(cin, adad.str1);
    int lee = adad.str1.length();
    adad.str2 = adad.str1;
    for (int i = 0;i < lee;i++) {
        if (adad.str1[i] >= 48 && adad.str1[i] <= 57) {
            counter++;
            adad.str2[i] = '*';
        }
    }
    cout << "str1 = " << adad.str1 << endl;
    cout << "The number of the digits in the str1 is " << counter << "." << endl;
    cout << "str2 = " << adad.str2;
}