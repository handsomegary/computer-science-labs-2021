#include <iostream>
#include<vector>
#include<string>
using namespace std;
int count =1;
void show(int number)
{
    vector <int> a;
    int num;
    while(number!=0)
    {
       num=number%10;
       a.push_back(num);
       number=number/10;
    }
    int i=a.size();
    for(int k=i-1;k>=0;k--)
    {
        if(k!=0)
            cout<<a[k]<<"+";
        else
            cout<<a[k];
    }

    count++;
}
int add(int number)
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
        sum+=n;
    return sum;
}
string f(int a)
{
    if(a!=1)
        return "f("+f(a-1)+")";
    else
        return "f(n)";
}


int main()
{
    int number;

    cin>>number;
    while(number<0)
    {
        cout << "You should input a positive integer" << endl;
        cin>>number;
    }
    while(number>=10)
    {
        cout<<f(count)<<"=";
        show(number);
        cout<<"="<<add(number)<<endl;
        number=add(number);
    }
    cout<<"The summing digit is:"<<number<<endl;

    return 0;
}
