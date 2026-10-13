// 2024 P113021: return the minimum through the required function.
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

double minimum(double x, double y, double z) {
    double result = x;
    if (y < result) result = y;
    if (z < result) result = z;
    return result;
}
int main() {
    double x, y, z;
    if (!(cin >> x >> y >> z) || !isfinite(x) || !isfinite(y) || !isfinite(z)) {
        cout << "error\n";
        return 1;
    }
    cout << setprecision(15) << minimum(x, y, z) << '\n';
}
