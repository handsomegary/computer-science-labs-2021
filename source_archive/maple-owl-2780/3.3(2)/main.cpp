#include <iostream>

using namespace std;

int main()
{
    long long int bina;
    int d,a,c=1;
    cout<<"Please input an unsigned binary number: ";

    cin>>bina;
    while(bina!=0){
        a=bina%10;
        d=d+a*c;
        c*=2;
        bina/=10;

    }
    cout << "The corresponding decimal number is " << d;
















    return 0;
}
