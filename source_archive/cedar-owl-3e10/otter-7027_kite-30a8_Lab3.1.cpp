//lab3.1
#include <iostream>

using namespace std;

int main()
{
    int number1,number2,number3;
    cout<<"Please enter 3 different integers:"<<endl;
    cin>>number1>>number2>>number3;
    if(number1>number2)
    {
        int a=number2;
        number2=number1;
        number1=a;
    }
    if(number1>number3)
    {
        int a=number3;
        number3=number1;
        number1=a;
    }
    if(number2>number3)
    {
        int a=number3;
        number3=number2;
        number2=a;
    }
    cout<<"The sorting result from small to large is "<<number1<<"->"<<number2<<"->"<<number3<<endl;
    return 0;





}
