#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double squareroot(double, double, double);
double recalculation(double, double, double);

double squareroot(double i,double n, double n1)
{
    if (n - n1 < 0.000000000000000001)
    {
        return n1;
    }
    else
    {
        return recalculation(i, n, n1);
    }


}
double recalculation(double k,double a, double b)
{
    return squareroot(k, (a+b)/2, (k*2)/(a+b) );
}

int main()
{
    double i;
    cout << "Enter a number: ";
    cin >> i;
    while(i < 0)
    {
        cout << "The number is out of range. Please enter again: ";
        cin >> i;
    }
    if (i == 0)
    {
        cout << 0;
    }
    else
    {
        i = squareroot(i, i, 1);
        cout << fixed <<setprecision(10) << floor(i*10000000000)/10000000000;
    }
    return 0;
}
