#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    unsigned long long sample;
    cout << "Enter # of sample: ";
    if (!(cin >> sample) || sample < 1 || sample > 4294967295ULL) return 1;
    unsigned long long counts[5] = {};
    long double mean = 0, m2 = 0;
    srand(static_cast<unsigned>(time(0)));
    for (unsigned long long i = 1; i <= sample; ++i) {
        const int score = rand() % 100 + 1;
        const int grade = score >= 90 ? 0 : score >= 80 ? 1 : score >= 70 ? 2 : score >= 60 ? 3 : 4;
        ++counts[grade];
        // Welford's algorithm: population variance without cancellation.
        const long double delta = score - mean;
        mean += delta / i;
        m2 += delta * (score - mean);
    }
    const char grades[] = "ABCDF";
    for (int i = 0; i < 5; ++i) cout << grades[i] << ": " << counts[i] << '\n';
    cout << fixed << setprecision(2) << "Mean: " << mean << '\n'
         << "STD Deviation: " << sqrt(m2 / sample) << '\n';
}
