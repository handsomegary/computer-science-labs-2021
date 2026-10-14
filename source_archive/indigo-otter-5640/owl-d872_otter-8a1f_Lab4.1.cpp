#include <iostream>
using namespace std;

int main()
{
    long long int number;
    int prime = 2;
    cout << "Enter a number: ";
    cin >> number;
    while (number < 2 || number > 2147483647)
    {cout << "Please enter a correct number: ";
    cin >> number;}
    cout << number << " = ";
    while ( number != 1 )
    {if ( number % prime == 0 ){
            if (number == prime)
                {cout << prime;
                number = number / prime;}
            else
                {cout << prime << "*";
                number = number / prime;}}
    else{prime = prime + 1;}
        }
    return 0;
}
