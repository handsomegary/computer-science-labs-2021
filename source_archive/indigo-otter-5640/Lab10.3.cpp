#include <iostream>
#include <string>
using namespace std;

string select5_ifyes(string[],string[],int[],int*);
int select5_ifno(string[],string[],int[]);
int main()
{
    int a = 0;
    string username;
    string account[16] = {"0"},password[16] = {"0"};
    int status[16];
    int log = 20;
    char select[3];
    while(true)
    {
     if(a == 1)cout<< "welcome " << username <<endl;
    cout << "Do you have an account ? ";
    cin.getline(select,2);
    if(select[0]=='y'){username=select5_ifyes(account,password,status,&a);}
    else select5_ifno(account,password,status);

    } return 0;

}

string select5_ifyes(string account[16],string password[16],int status[16],int *a)
{
    int state=0;
    string username,passwod,null;
    int name=0,pass=0;

    cout<<"please enter user name: ";
    getline(cin,username);
    cout<<"please enter password: ";
    getline(cin,passwod);

    for(int i=0;i<16;i++)
    {
        if(username==account[i])
        {
            name=1;
            state=i;
        }
    }
    for(int i=0;i<16;i++)
    {
        if(passwod==password[i])
        {
            pass=1;
        }
    }
 if(pass==1&&name==1){cout<<"login successfully"<<endl;*a=1;return username;}
 else {cout<<"no match account"<<endl;}

}
int select5_ifno(string account[16],string password[16],int status[16])
{
    char select[3];
    cout<<"Do you want to create an account ?";
    cin.getline(select,2);
    if(select[0]=='y')
    {
        int state=0;
        while(status[state]==1)state++;
        cout<<"please enter user name: ";
        getline(cin,account[state]);
        cout<<"please enter password: ";
        getline(cin,password[state]);
        status[state]=1;
        cout<<"please login again"<<endl;


    }
    else cout<<"have a nice day"<<endl;
}

