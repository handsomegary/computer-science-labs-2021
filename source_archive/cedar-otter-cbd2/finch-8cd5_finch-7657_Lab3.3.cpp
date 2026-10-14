#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    long long int x;
    int y = 0;
    int z;
    int w = -1;
    cout << "Please input an unsigned binary number: ";
    cin >> x;
    while (x > 0)
    {
        w += 1;
        z = x % 10;
        y = y + pow(2, w) * z;
        x = x / 10;
    }
    cout << "The corresponding decimal number is " << y;
    return (0);
}
