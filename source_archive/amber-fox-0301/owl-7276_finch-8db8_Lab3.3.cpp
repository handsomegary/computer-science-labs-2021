#include <iostream>
#include <cmath>

using namespace std;

int main()
{




    long long int ent,dec,deg,dec_t,result;
    deg=0;


     cout<<"Please input an unsigned binary number: ";
    cin>> ent;
    dec=0;

    while(ent>0)
    {
     dec+=(ent%10)*pow(2,deg);
     ent=ent/10;
     deg++;

    }

   cout<<"The corresponding decimal number is "<<dec;

    return 0;
}
