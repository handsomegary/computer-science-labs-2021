#include <iostream>
#include <vector>
#include<string>
using namespace std;

int main()
{
    int a[26]={0};
    int b[26]={0};
    bool flag=true;
    string str1;
    string str2;
    cin>>str1>>str2;
    for(int i=0;i<str1.length();i++)
    {
        a[str1[i]-97]++;
    }
    for(int i=0;i<str2.length();i++)
    {
        b[str2[i]-97]++;
    }
    for(int i=0;i<26;i++)
    {
        if(a[i]!=b[i])
        {
            flag=false;
            break;
        }
    }
    if(flag==true)
        cout<<"Yes! It's anagram."<<endl;
    else
        cout<<"No! It is not anagram."<<endl;
    return 0;
}
