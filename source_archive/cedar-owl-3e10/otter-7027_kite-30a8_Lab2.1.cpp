//lab2.1
#include <iostream>

using namespace std;

int main()
{
    double f,c;  //Fahrenheit Celsius
    cout<<"Please input temperature value in Celsius degree: ";
    cin>>c; // input Celsius

    f=c*9/5+32;// translate Fahrenheit
    cout<<"The corresponding value in Fahrenheit degree is: "<<f<<endl;
    return 0;

}  //end of main


