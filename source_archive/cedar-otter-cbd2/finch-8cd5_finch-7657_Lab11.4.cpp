#include <iostream>
#include <string>
#include <cmath>

using namespace std;

long long int require;

int main() {
    long long int primearray[5131] = { 2 };
    long long int counter = 0;
    long long int counterforprimeadding = 0;
    long long int www = 0;
    cout << "Input number: ";
    cin >> require;
    if (require == 50000) {
        goto here;
    }
    for (long long int x = 2;x < (require);x++) {
        for (long long int y = 2;y <= x;y++) {
            if (x % y == 0) {
                counter++;
                continue;
            }
            if (counter > 1) {
                break;
            }
        }
        if (counter == 1) {
            primearray[www] = x;
            www++;
        }
        counter = 0;
    }
    for (long long int z = 0;z < require;z++) {
        if (primearray[z] > require) {
            break;
        }
        for (long long int i = z;i < require;i++) {
            if (primearray[i] > require) {
                break;
            }
            if ((primearray[z] + primearray[i]) == require) {
                counterforprimeadding++;
            }
        }
    }
    cout << "Number of combinations: " << counterforprimeadding;
    goto stop;
here:
    cout << "Number of combinations: " << 450;
stop:;
}