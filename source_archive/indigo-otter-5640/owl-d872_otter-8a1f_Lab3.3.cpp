#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    long long int enter,dec,deg,dec_t,result;
    deg = 0;
    cout << "Please input an unsigned binary number: ";
    cin >> enter;
    dec = 0;
    while (enter>0)
    {
     dec += (enter%10)*pow(2,deg);
     enter = enter/10;
     deg = deg + 1;
     }
    cout<<"The corresponding decimal number is "<<dec;
    return 0;
}
