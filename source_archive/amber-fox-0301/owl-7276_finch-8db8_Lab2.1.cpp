#include <iostream>

using namespace std;

int main()
{
    float c;
    cout << "Please input temperature value in Celsius degree: ";
    cin>> c;
    cout << "The corresponding value in Fahrenheit degree is: "<<c*9/5+32;
    return 0;
}
