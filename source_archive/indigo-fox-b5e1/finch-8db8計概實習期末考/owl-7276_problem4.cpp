#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int check=0;
    string a,b;
    cin>>a>>b;
    if(a.length()!=b.length()){cout<<"No! It is not anagram.";return 0;}
    for(int i=0;i<=a.length();i++)
    {
        int control=0;

        while(control<=b.length())
        {
            if(a[i]==b[control])
            {
                b[control]=10;
                break;
            }
            control++;
            if(control==b.length()+1)check=1;
        }
    }

    if(check==0)cout<<"Yes! It's anagram.";
    else cout<<"No! It is not anagram.";
    return 0;
}


