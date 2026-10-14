//   Lab3.3
#include <iostream>
#include<cmath>
using namespace std;

int main()
{
    unsigned long long int i,a,sum=0;
    int p=0;
    cout<<"Please input an unsigned binary number: ";
    cin>>i;
    while(i!=0)
    {
        a=i%10;
        sum+=a*pow(2,p);
        i/=10;
        p++;
    }
    cout<<"The corresponding decimal number is "<<sum<<endl;
    return  0;
}
