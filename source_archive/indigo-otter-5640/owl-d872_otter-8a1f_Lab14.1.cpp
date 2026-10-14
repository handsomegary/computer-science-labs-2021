#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

int k = 0;
int w = 0;

int main()
{
    string arithmetic;
    //int counter = 0;
    cout << "Please enter the arithmetic: ";
    cin >> arithmetic;
    int array[100];
    char array1[100];
    int start = 0;
    string number;
    for (int i = 0; i < arithmetic.length(); i++)
    {
        if(arithmetic[i] < '0' || arithmetic[i] > '9')
        {
            //cout<<i<<" "<<arithmetic[i]<<" "<<start<<" "<<i-start<<endl;
            number = arithmetic.substr(start, i - start);
            //cout<<number<<"a"<<endl;
            start = i + 1;
            //cout<<k<<"ss"<<endl;
            array[k++] = stoi(number);
        }
        if (i == arithmetic.length() - 1)//take the last number
        {
            number = arithmetic.substr(start, i + 1 - start);
            //cout<<number<<endl;
            array[k++] = stoi(number);
            //cout<<"c"<<endl;
            //cout<<stoi(number)<<endl;
        }
    }
    for (int i = 0; i < arithmetic.length(); i++)
    {
        if (arithmetic[i] < 48 || arithmetic[i] > 57)//take calculating operator out
        {
            array1[w] = arithmetic[i];
            w++;
            if (arithmetic[i] == '*' || arithmetic[i] == '/' || arithmetic[i] == '%')
            {
                //counter++;
            }
        }
    }
    for (int i = 0;i < w;i++)
    {
        if (array1[i] == '*')
        {
            array[i + 1] *= array[i];
            array[i] = 0;
            array1[i] = '+';//change the number into 0+0+0+0...
            //counter--;
        }
        if (array1[i] == '/')
        {
            array[i + 1] = array[i] / array[i + 1];
            array[i] = 0;
            array1[i] = '+';
            //counter--;
        }
        if (array1[i] == '%')
        {
            array[i + 1] = array[i] % array[i + 1];
            array[i] = 0;
            array1[i] = '+';
            //counter--;
        }
    }
    // for (int i = 0;i < k;i++) {
    //     cout << array[i] << endl;
    // }
    for (int i = 0;i < w;i++)
    {
        if (array1[i] == '+')
        {
            for (int aa = i + 1;aa < k;aa++)
            {
                if (array[aa] != 0)
                {
                    array[0] += array[aa];
                    array[aa] = 0;
                    break;
                }
                else continue;
            }
        }
        if (array1[i] == '-')
        {
            for (int n = i + 1;n < k;n++)
            {
                if (array[n] != 0)
                {
                    array[0] -= array[n];
                    array[n] = 0;
                    break;
                }
                else continue;
            }
        }
    }
    cout << array[0];
}
