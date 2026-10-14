#include<iostream>
using namespace std;

int main()
{
    long int number;
    long int i = 2;
    cout << "Enter a number: ";
    cin >> number;
    while(number < 2 || number > 2147483647)
    {cout << "Please enter a correct number: ";
    cin >> number;}
    cout << number << " = ";
    while( number > 1 )
    {
        while( number%i == 0 )
        {
        cout << i << "*";
        number = number/i;
        }
        i = i+1;
    }
    cout << "\b \b";
    return 0;
}
