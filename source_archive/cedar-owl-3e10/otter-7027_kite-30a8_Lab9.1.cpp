#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a,b;

    cout << "Input Line1: ";
    getline(cin,a);
    cout<<"Input Line2: ";
    getline(cin,b);
    a[0]=a[0]-32;
    for(int i=0;i<a.length();i++)
    {
        if(a[i]==32)
           a[i+1]=a[i+1]-32;
    }



    b[0]=b[0]-32;


    for(int i=0;i<b.length();i++)
     {
          if(b[i]==32)
          b[i+1]=b[i+1]-32;
     }




    cout<<"Output Line: "<<a<<" "<<b;
    return 0;
}
