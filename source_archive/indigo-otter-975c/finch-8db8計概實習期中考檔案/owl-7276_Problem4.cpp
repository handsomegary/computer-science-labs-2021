#include <iostream>
#include <cmath>
//the program is to find  Armstrong Number
using namespace std;

int func1(int);
int degitcheck(int);
int main()
{
    int bound1,bound2;
    cin>>bound1>>bound2;
    for(int i=bound1;i<=bound2;i++)
    {
       func1(i);
    if(func1(i)==1)
     {  cout<<i;
        for(int j=i+1;j<=bound2;j++)
        {
        func1(j);
        if(func1(j)==1)cout<<" & "<<j;

        }return 0;
     }
    }cout<<"none";

}


int degitcheck(int input)
{
    int i = 0;
    int k = input / pow(10, i);

    while (k > 0)
    {
        i++;
        k = input / pow(10, i);
    }
    return i ;
}
int func1 (int i)
{
    int degit=degitcheck(i);
    int temp = 0;
    int input=i;
    while (input > 0)
    {
        int k=input%10;
        temp +=pow(k,degit);
        input /= 10;
    }


    if(i==temp) return 1;
    else return 0;


}
