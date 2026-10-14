#include <iostream>
#include <vector>
#include<cmath>

using namespace std;
int cal(int number)
{
    int a=0;
    while(number!=0)
    {
        a++;
        number/=10;
    }
    return a;
}
int add(int number,int p)
{
    vector <int> a;
    int num;
    while(number!=0)
    {
       num=number%10;
       a.push_back(num);
       number=number/10;
    }
    int sum=0;
    for(auto n:a)
    {
        sum=sum+pow(n,p);
    }
    return sum;
}


int main()
{
    int low,up;

    vector <int> a;
    cin>>low>>up;
    for(int i=low;i<=up;i++)
    {
        int p=cal(i);
        int sum=add(i,p);
        if(i==sum)
            a.push_back(i);

    }
     int i=a.size();
    for(int k=0;k<a.size();k++)
    {
        if(k!=a.size()-1)
            cout<<a[k]<<" & ";
        else
            cout<<a[k];
    }
    if(a.empty())
        cout<<"none";




    return 0;
}
