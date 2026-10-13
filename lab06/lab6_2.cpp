#include <cmath>
#include <iostream>
#include <limits>
using namespace std;

void rectangleArea(long long x, long long y) { cout << x * y; }
void rectanglePerimeter(long long x, long long y) { cout << 2 * (x + y); }
void trianglePerimeter(long long x, long long y, long long z) { cout << x + y + z; }
void triangleArea(long long x, long long y, long long z) {
    const long double s = (static_cast<long double>(x) + y + z) / 2;
    cout << static_cast<long long>(round(sqrt(s * (s-x) * (s-y) * (s-z))));
}

int main() {
    long long a, b, c;
    while (true) {
        cout << "Input 3 Numbers: ";
        if (!(cin >> a >> b >> c)) {
            if (cin.eof()) return 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "error\n";
            continue;
        }
        if (a < 1 || b < 1 || c < 1 || a > 2147483647LL || b > 2147483647LL ||
            c > 2147483647LL || a + b <= c || b + c <= a || a + c <= b) {
            cout << "error\n";
            continue;
        }
        break;
    }
    cout << "Perimeter of the rectangle: "; rectanglePerimeter(a,b); cout << '\n';
    cout << "Area of the rectangle: "; rectangleArea(a,b); cout << '\n';
    cout << "Perimeter of the triangle: "; trianglePerimeter(a,b,c); cout << '\n';
    cout << "Area of the triangle: "; triangleArea(a,b,c); cout << '\n';
}
