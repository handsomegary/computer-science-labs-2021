#include <iostream>

using namespace std;

int main()
{
    int a1,a2,oper;
    cout<<"Please input 2 different integers:\n";
    cin>> a1>>a2;
    cout<<"Please input the operation:\n";
    cin>>oper;

    if(oper==1)
        cout<<"Summation is "<<a1+a2;
    if(oper==2)
        cout<<"Multiplication is "<<a1*a2;
    if(oper==3){
        if(a1>a2)
            cout<<"Larger number is "<<a1;
        else
            cout<<"Larger number is "<<a2;

    }
    if(oper==4){
        if(a1<a2)
            cout<<"Smaller number is "<<a1;
        else
            cout<<"Smaller number is "<<a2;
    }





}
