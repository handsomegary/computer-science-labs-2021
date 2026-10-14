#include <iostream>
#include<iomanip>
#include<cmath>

using namespace std;
double square_root(double,double,long long int);

int main()
{
    long long int number=0,i=1;
    double low=0,up=0,root;


    cout << "Enter a number: ";
    cin>>number;
    while(number<0)
    {
        cout<<"The number is out of range. Please enter again: ";
        cin>>number;
    }
    while(number>0)
    {
       if(number>=i*i&&number<=(i+1)*(i+1))
       {
         low=i;
         up=i+1;
         break;
       }
       i++;
    }

     if(up*up==number)
    {
        root=up;
        cout<<setprecision(10)<<fixed<<root<<endl;
    }
   else
   {
        root=square_root(low,up,number);
        cout<<setprecision(10)<<fixed<<floor(root*1e10)/1e10<<endl;

   }




    return 0;
}

double square_root(double low,double up,long long int number)
{
    double mid=(low+up)/2;

    if(abs(mid*mid-number)<=1e-14)
        return mid;
    else if(number>=low*low&&number<=mid*mid)
        return square_root(low,mid,number);
    else  if(number>=mid*mid&&number<=up*up)
        return square_root(mid,up,number);
}

