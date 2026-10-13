// 2024 P113024: capacities and their sum are widened before arithmetic.
#include <iostream>
using namespace std;

long long gcd(long long a, long long b) {
    while (b) { const long long remainder = a % b; a = b; b = remainder; }
    return a;
}
bool canMeasureWater(long long x, long long y, long long z) {
    if (x <= 0 || y <= 0 || x == y || z <= 0 || z > x + y) return false;
    return z % gcd(x, y) == 0;
}
int main() {
    long long x, y, z;
    if (!(cin >> x >> y >> z) || x > 2147483647LL || y > 2147483647LL) return 1;
    cout << canMeasureWater(x, y, z) << '\n';
}
