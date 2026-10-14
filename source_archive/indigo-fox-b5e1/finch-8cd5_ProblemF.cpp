#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    float a[50] = {};
    cout << "Please enter the scores of all students:" << endl;
    int input = 0;
    int counter = 0;
    int counterfail = 0;
    int counterwhich = 1;
    double sum = 0;
    while (cin >> input) {
        a[counter++] = input;
        char ch = getchar();
        sum += input;
        if (input < 70) {
            counterfail++;
        }
        if (ch == '\n')
            break;
    }

    cout << "avg = " << setprecision(4) << sum / counter << endl;
    if (counterfail != 0) {
        cout << "fail:" << endl;
    }
    cout.unsetf(ios_base::fixed);
    for (int i = 0;i < counter;i++) {
        if (a[i] < 70) {
            cout << i + 1 << ": " << a[i] << endl;
            counterwhich++;
        }
    }

    return 0;
}
