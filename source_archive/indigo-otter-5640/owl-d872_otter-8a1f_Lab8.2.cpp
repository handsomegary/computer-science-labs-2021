#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d[100] = {0}, i, j, sum = 0;
    cout << "Please enter the first term(a1), the common difference(d) and the number of terms(n):" << endl;
    cin >> a >> b >> c;
    d[0] = a;
    if(a < 0)
    {
        cout << "The arithmetical series: " << "(" << a << ")";
    }
    else
    {
        cout << "The arithmetical series: " << a;
    }

    for(i = 1; i < c; i++)
    {
        a+=b;
        if(a < 0)
        {
            cout << " + " << "(" << a << ")";
        }
        else
        {
            cout << " + " << a;
        }
        d[i] = a;
    }
    for (j = 0; j < c; j++)
    {
        sum+=d[j];
    }
    if(sum < 0)
    {
        cout << " = " << "(" << sum << ")";
    }
    else
    {
        cout << " = " << sum;
    }
    return 0;
}
