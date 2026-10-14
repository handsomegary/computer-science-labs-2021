#include <iostream>

using namespace std;

int main()
{
    float num1,num2,o;



    cout << "Please input 2 different integers:  \n";
    cin>> num1>>num2;
    cout << "Please input the operation: "<<endl;
    cin >>o;
    if(o==1)
        cout <<"Summation is "<<num1+num2<<endl;
    if(o==2)
        cout <<"Multiplication is "<< num1*num2<<endl;
    if(o==3)
    {
        if(num1>num2)
            cout<< "Larger number is "<<num1<<endl;
        else
            cout<< "Larger number is "<<num2<<endl;
    }
    if(o==4)
    {
        if(num1>num2)
            cout<< "Smaller number is "<<num2<<endl;
        else
            cout<< "Smaller number is "<<num1<<endl;
    }
    return 0;
}
