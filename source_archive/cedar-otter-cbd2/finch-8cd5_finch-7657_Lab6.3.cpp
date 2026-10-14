#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    long long int a;
    int c;
    int A = 0;
    int B = 0;
    int C = 0;
    int D = 0;
    int E = 0;
    int F = 0;
    double g = 0;
    double k = 0;
    cout << "Enter # of sample: ";
    cin >> a;
    srand(time(0));
    for (int b = 1;b <= a;b++) {
        c = rand() % 101;
        if (c >= 90) {
            A++;
        }
        if (c < 90 && c >= 80) {
            B++;
        }
        if (c < 80 && c >= 70) {
            C++;
        }
        if (c < 70 && c >= 60) {
            D++;
        }
        if (c < 60) {
            F++;
        }
        g += c;
        k += (c * c);
    }
    cout << "A: " << A << endl << "B: " << B << endl << "C: " << C << endl << "D: " << D << endl << "F: " << F << endl;
    cout << "Mean: " << fixed << setprecision(2) << g / a << endl;
    cout << "STD Deviation: " << sqrt((k / a) - (g * g / a / a));
}