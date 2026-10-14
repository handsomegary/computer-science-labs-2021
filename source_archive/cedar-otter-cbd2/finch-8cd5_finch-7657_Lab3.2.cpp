#include <iostream>

using namespace std;

int main()
{
    int x;
    long long int z = 1;
    cout << "Please enter a nonnegative integer: ";
    cin >> x;

    while (x > 1)
    {
        z = z * x;
        x -= 1;
    }
    cout << "The corresponding factorial is " << z;

    return (0);
}
