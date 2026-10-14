#include <iostream>

using namespace std;

int main()
{
    long long int a;
    long long int b;
    long long int c;
    int d;
    int e;
    while (1)
    {
        cout << "Enter a: ";
        cin >> a;
        if (a == -1)
        {
            cout << "Bye~" << endl;
            break;
        }
        cout << "Enter b: ";
        cin >> b;
        cout << "Enter Cin: ";
        cin >> c;

        if (a > 1 || a < 0 || b < 0 || b > 1 || c > 1 || c < 0)
            cout << "!!! Enter the inputs again !!!" << endl;
        else
        {
            cout << "--------------------" << endl;
            cout << "  A  B  Cin Sum Cout" << endl;

            if ((!a && !b && c) || (!a && b && !c) || (a && !b && !c) || (a && b && c))
                d = 1;
            else
                d = 0;
            if ((b && c) || (c && a) || (a && b))
                e = 1;
            else
                e = 0;
            cout << "  " << a << "  " << b << "    " << c << "   " << d << "    " << e << endl;
            cout << "--------------------" << endl;
        }
    }

    return 0;
}