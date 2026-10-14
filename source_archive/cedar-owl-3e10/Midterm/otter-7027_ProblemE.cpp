#include <iostream>

using namespace std;
int add(int a[],int num)
{
    int ma=a[0],mi=a[0];
    for(int i=0;i<num;i++)
    {
        if(ma<a[i])
            ma=a[i];
    }
    for(int i=0;i<num;i++)
    {
        if(mi>a[i])
            mi=a[i];
    }
    return ma+mi;
}
long long int decimal_to_binary(int number)     //decimal translate to binary
{
    if(number/2!=0)
        return number%2+10*decimal_to_binary(number/2);
    else
        return (number%2);
}
long long int decimal_to_oct(int number)     //decimal translate to oct
{
    if(number/8!=0)
        return number%8+10*decimal_to_oct(number/8);
    else
        return (number%8);
}

int main()
{
    int num,average;
    do
    {
       cin>>num;
       int a[num];
       for(int i=0;i<num;i++)
            cin>>a[i];
        if(add(a,num)%2!=0)
        {
            cout<<"Input again!"<<endl;
            continue;
        }
        else
        {
            average=add(a,num)/2;
            break;

        }

    }while(true);
    int oct,binary;
    oct=decimal_to_oct(average);
    binary=decimal_to_binary(average);
    cout<<"Decimal "<<average<<endl;
    cout<<"Octet "<<oct<<endl;
    cout<<"Binary "<<binary<<endl;
    if(binary>=111111)
        cout<<"The country is rich";
    else
        cout<<"Come on";


    return 0;
}
