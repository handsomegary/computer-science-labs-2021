// 2024 P1130292: integer halving follows the lecture's recursive area hint.
#include <iostream>
using namespace std;

bool prime(long long number) {
    if (number < 2) return false;
    if (number % 2 == 0) return number == 2;
    for (long long divisor = 3; divisor <= number / divisor; divisor += 2)
        if (number % divisor == 0) return false;
    return true;
}
long long area(long long x, long long y) {
    if (prime(x) || prime(y)) return x * y;
    if (x <= 1 && y <= 1) return 0;
    if (x >= y) return area(x / 2, y);
    return area(y / 2, x);
}
int main() {
    long long x, y;
    if (!(cin >> x >> y) || x < 1 || y < 1 || x > 2147483647LL || y > 2147483647LL) {
        cout << "error\n";
        return 1;
    }
    const long long result = area(x, y);
    if (result == 0) cout << "error\n";
    else cout << result << '\n';
}
