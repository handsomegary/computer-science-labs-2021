#include <iostream>

using namespace std;

int main()
{
    int a;
    int b;
    int c;
    int d;
    int e;
    while(true)
    {
        cout << "Enter a: ";
        cin >> a;
        if(a==-1 || b==-1 || c==-1)
        {
            cout << "Bye~";
            return 0;
        }
        else{}
        cout << "Enter b: ";
        cin >> b;
        cout << "Enter Cin: ";
        cin >> c;

        while((a!=0 && a!=1) || (b!=0 && b!=1) || (c!=0 && c!=1))
        {
            cout << "!!! Enter the inputs again !!!" << endl;
            cout << "Enter a: ";
            cin >> a;
            cout << "Enter b: ";
            cin >> b;
            cout << "Enter Cin: ";
            cin >> c;
        }
        if((a+b+c)%2 == 1)
        {
                d = 1;
        }
        else
        {
            d = 0;
        }
        if((a+b+c)/2 == 1)
        {
            e = 1;
        }
        else
        {
            e = 0;
        }
        cout << "--------------------" << endl << "  A  B  Cin Sum Cout" << endl << "  " << a << "  " << b << "    " << c << "   " << d << "    " << e << endl << "--------------------" << endl;

    }

    return 0;
}
