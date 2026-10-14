#include <iostream>

using namespace std;

int main()
{
    long long int x;
    int y = 2;
    cout << "Enter a number: ";
    cin >> x;
    while (x < 2)
    {
        cout << "Please enter a correct number: ";
        cin >> x;
    }
    cout << x << "=";
    while (x > 1)
    {
        while (x % y == 0)
        {
            cout << y;
            x = x / y;
            if (x == 1)
            {
                break;
            }
            cout << "*";
        }
        y += 1;
    }
    return 0;
}