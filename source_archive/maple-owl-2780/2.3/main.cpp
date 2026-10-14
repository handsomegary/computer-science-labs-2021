#include <iostream>

using namespace std;

int main()
{
    float weight;
    float height;
    double b;




    cout<<"Please enter your weight: ";
    cin>>weight;
    cout<<"Please enter your height: ";
    cin>>height;
    b=weight/(height*height);

    cout<<"Your BMI is "<<b<<endl;
    if(b>=18.5 && b<=24)
        cout<<"You are healthy";
    if(b>24)
        cout<<"You need to control your diet";
    if(b<18.5)
        cout<<"You need to eat more";

    return 0;
}
