// Based on the original lab; use the mandated driver struct and n<=100.
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct driver { int distance; int fine; };
int main() {
    int n, d, r;
    while (cin >> n >> d >> r && !(n == 0 && d == 0 && r == 0)) {
        if (n < 1 || n > 100 || d < 1 || d > 10000 || r < 1 || r > 5) return 0;
        vector<int> morning(n), evening(n);
        for (int i = 0; i < n; ++i) if (!(cin >> morning[i])) return 0;
        for (int i = 0; i < n; ++i) if (!(cin >> evening[i])) return 0;
        sort(morning.begin(), morning.end());
        sort(evening.rbegin(), evening.rend());
        vector<driver> drivers(n);
        int total = 0;
        // Pair shortest with longest: exchanging crossed pairs cannot reduce this cost.
        for (int i = 0; i < n; ++i) {
            drivers[i].distance = morning[i] + evening[i];
            drivers[i].fine = max(0, drivers[i].distance - d) * r;
            total += drivers[i].fine;
        }
        cout << total << '\n';
    }
}
