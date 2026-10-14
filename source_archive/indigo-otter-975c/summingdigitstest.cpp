#include <iostream>
#include <cmath>
using namespace std;

int fn1(int n)
{
    int sum = 0;
    int k;
    int division;
    int l;
    while(n > 0)
    {
        for(k = 18; k >= 0; k--)
        {
            l = pow(10,k);
            division = n/l;
            sum = sum + division;
            n %= l;
        }
    }
    cout << sum;
}

void fn2(int n)
{
    int sum = 0;
    int k;
    int division;
    int l;
    while(n > 0)
    {
        for(k = 18; k >= 0; k--)
        {
            l = pow(10,k);
            division = n/l;
            sum = sum + division;
            n %= l;
            if(division > 0 && n > 1)
            {
                cout << division << "+";
            }
            else if(division != 0)
            {
                cout << division;
            }
            else{}
        }
    }
    cout << "=" << sum;
}
int main()
{
    int n;
    cin >> n;
    if (n < 0)
    {
        cout << "You should input a positive integer" << endl;
        cin >> n;
    }
    cout << "f(n)=";
    fn2(n);
    cout << "\nThe summing digit is:";
    fn1(n);
    return 0;
}

