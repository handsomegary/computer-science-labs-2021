
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

long long int paw (int a,int b  )
{
    if (b==0) return 1;
    else return a*paw(a,b-1);
}

long double root(long long int ent,long long int call,int digit )
{
    if (digit==1) return call;
    return ((root(ent,call,digit-1)+ent/(root(ent,call,digit-1)))/2);
}


int main()
{
    unsigned long long int ent,call=1 ;
    cout << "Enter a number: " ;
    cin>> ent;

    while (ent<0||ent>paw(2,63))
    {
       cout<<"The number is out of range. Please enter again: ";
       cin>> ent;
    }

    while (call*call<ent)
    {
        call++;
    }

if(ent==0||ent==1){cout<<ent<<endl; return 0;}


    long long int result=root (ent,call-1,10)*paw(10,10);
    double result2=result;
    double result3=result2/paw(10,10);
    int j=0;
    while(pow(10,j)<result3)
    {
        j++;
    }
    cout<<setprecision(10+j)<<result3<<endl;

}
