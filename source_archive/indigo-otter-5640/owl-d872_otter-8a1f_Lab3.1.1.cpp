#include <iostream>
using namespace std;

unsigned long long dec2bin(unsigned long long);

int main()
{
    unsigned long long bin = dec2bin(152341);
    cout << "binary = " << bin << endl;
    return 0;
}

unsigned long long dec2bin (unsigned long long number)
{
    unsigned long long bin = 0;
    unsigned long long i = 1;
    while(number > 0)
    {
        bin += (number%2)*i;
        cout << bin << endl;
        number = number/2;
        cout << number << endl;
        i *= 10;
    }
    return bin;
}
