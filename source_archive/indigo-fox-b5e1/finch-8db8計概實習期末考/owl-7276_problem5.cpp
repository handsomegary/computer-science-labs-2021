#include <iostream>
#include <cstring>
using namespace std;


void encoder();
void decoder();
int main()
{
   int select;
    //int A='J';
    cout << "Welcome to encryption system!" << endl
          << "Enter 1 to encrypt"<<endl
          << "Enter 2 to decrypt"<<endl;
    cin>>select;
    cin.get();
    cout<<endl;
    switch (select)
    {
        case 1:encoder();break;
        case 2:decoder();break;
        default:break;
    }

    return 0;
}

void encoder()
{
    string enter ;
    cout<<"Input information: ";
    getline(cin,enter);
    //cout<<enter<<endl;
    for(int i=0;i<=enter.length();i++)
    {
        if(enter[i]==' ');
        else{
          switch(i%2)
        {
            case 0:enter[i]=enter[i]+9;break;
            case 1:enter[i]=enter[i]-3;break;
        }
        }

    }
    cout<<"Encrypted information: "<<enter;
}

void decoder()
{
    string enter ;
    cout<<"Input information: ";
    getline(cin,enter);
    for(int i=0;i<=enter.length();i++)
    {
        if(enter[i]==' ');
        else{
          switch(i%2)
        {
            case 0:enter[i]=enter[i]-9;break;
            case 1:enter[i]=enter[i]+3;break;
        }
        }

    }
    cout<<"Decrypted information: "<<enter;
}

