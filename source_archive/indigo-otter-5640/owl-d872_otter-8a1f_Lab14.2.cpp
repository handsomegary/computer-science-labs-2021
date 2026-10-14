#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str, str2;
    cout << "Please enter a string."<< endl;
    getline(cin, str);
    cout << "str1 = " << str << endl;
    int digits = 0;
    for(int i = 0; i < str.length(); i++)
    {
        /*cout << str[i] - '0' << " ";*/
        if( (str[i] - '0') >= 0&& (str[i] - '0') <= 9)
        {
            digits++;
        }
    }
    cout << "The number of the digits in the str1 is " << digits << "." << endl;
    cout << "str2 = ";
    for(int i = 0; i < str.length(); i++)
    {
        if( (str[i] - '0') >= 0&& (str[i] - '0') <= 9)
        {
            cout<<'*';
        }
        else
        {
            cout << str[i];
        }
    }
}
