#include <iostream>
#include <cmath>

using namespace std;

void rectanglePerimeter(long long int a, long long int b) {
    cout << "Perimeter of the rectangle: " << (a + b) * 2 << endl;
}
void rectangleArea(long long int a, long long int b) {
    cout << "Area of the rectangle: " << a * b << endl;
}
void trianglePerimeter(long long int a, long long int b, long long int c) {
    cout << "Perimeter of the triangle: " << a + b + c << endl;
}
void triangleArea(long long int a, long long int b, long long int c) {
    cout << "Area of the triangle: " << round(sqrt((a + b + c) * (b + c - a) * (a + b - c) * (a + c - b) / 16)) << endl;
}
int main() {
    while (1) {
        long long int a, b, c;
        cout << "Input 3 Numbers: ";
        cin >> a >> b >> c;
        if (a + b <= c || a + c <= b || b + c <= a) {
            cout << "error" << endl;
            continue;
        }
        rectanglePerimeter(a, b);
        rectangleArea(a, b);
        trianglePerimeter(a, b, c);
        triangleArea(a, b, c);
        break;
    }
    return 0;
}
