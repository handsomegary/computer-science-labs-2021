#include <iostream>
#include <iomanip>
using namespace std;


void func1(int k) //for **
{
    for(int i=1;i<=k;i++)
    cout<<"*";

}


void func2(int k) //for **
{
    for(int i=1;i<=k;i++)
    cout<<" ";

}

int main()
{   int sise;


    cout <<"Enter the size of the diamond: ";
    cin>> sise;
    while(sise<3||sise>4294967295)
    {
        cout<<"Enter again: ";
        cin>> sise;
    }
    int k=(sise+1)/2;
    for(int level=1;level<=sise/2+1;level++)
    {
        func1(k);func2(2*level-1);func1(k);
        k--;
        cout<<endl;
    }
    int j=4;
    for(int level2=1;level2<=sise/2;level2++)
    {
        func1(level2+1);func2(sise+2-j);func1(level2+1);
         j=j+2;
        cout<<endl;

    }













   return 0;
    }


