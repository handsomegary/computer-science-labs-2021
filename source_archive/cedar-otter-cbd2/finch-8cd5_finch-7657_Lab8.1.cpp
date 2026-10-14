#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
int main() {
    float array[3];
    cout << "Please enter the scores of three students:" << endl;
    cin >> array[0] >> array[1] >> array[2];
    cout << "avg = " << fixed << setprecision(3) << (array[0] + array[1] + array[2]) / 3 << endl;
    cout.unsetf(ios_base::fixed);
    if (array[0] < 60 || array[1] < 60 || array[2] < 60) {
        cout << "fail:" << endl;
    }
    for (int i = 1;i <= 3;++i) {
        if (array[i - 1] < 60) {
            cout << i << ": " << array[i - 1] << endl;
        }
    }
}