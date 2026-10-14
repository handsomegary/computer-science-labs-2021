#include <iostream>

using namespace std;
struct example
{

   string str1;

   string str2;
};

int main()
{
    example no1;
    int count=0;
    cout<<"Please enter a string."<<endl;
    getline(cin,no1.str1);
    cout<<"str1 = "<<no1.str1<<endl;
    for(int i=0;i<no1.str1.length();i++)
    {
        if(no1.str1[i]<=57&&no1.str1[i]>=48)
        {
            no1.str1[i]='*';
            count++;
        }

    }

    cout<<"The number of the digits in the str1 is "<<count<<"."<<endl;
    cout<<"str2 = "<<no1.str1<<endl;
}
