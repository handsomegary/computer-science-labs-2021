// 2024 P113025: use two functions, without truncating Heron's semiperimeter.
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

void trianglePerimeter(long long x, long long y, long long z) {
    cout << "perimeter: " << x + y + z << '\n';
}
void triangleArea(long long x, long long y, long long z) {
    const long double s = (static_cast<long double>(x) + y + z) / 2;
    cout << "area: " << setprecision(6) << sqrt(s * (s-x) * (s-y) * (s-z)) << '\n';
}
int main() {
    long long x, y, z;
    if (!(cin >> x >> y >> z) || x < 1 || y < 1 || z < 1 || x > 2147483647LL ||
        y > 2147483647LL || z > 2147483647LL || x + y <= z || x + z <= y || y + z <= x) {
        cout << "error\n";
        return 0;
    }
    trianglePerimeter(x, y, z);
    triangleArea(x, y, z);
}
