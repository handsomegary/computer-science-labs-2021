#include <iostream>

using namespace std;

int main()
{
    int x;
    int y;
    int z;

    cout << "Please enter 3 different integers:" << endl;
    cin >> x;
    cin >> y;
    cin >> z;
    if (x > y && y > z)
    {
        cout << "The sorting result from small to large is " << z << "->" << y << "->" << x;
    }
    if (x > z && z > y)
    {
        cout << "The sorting result from small to large is " << y << "->" << z << "->" << x;
    }
    if (y > x && x > z)
    {
        cout << "The sorting result from small to large is " << z << "->" << x << "->" << y;
    }
    if (y > z && z > x)
    {
        cout << "The sorting result from small to large is " << x << "->" << z << "->" << y;
    }
    if (z > x && x > y)
    {
        cout << "The sorting result from small to large is " << y << "->" << x << "->" << z;
    }
    if (z > y && y > x)
    {
        cout << "The sorting result from small to large is " << x << "->" << y << "->" << z;
    }
    return (0);
}