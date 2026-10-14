#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

int select5( string&),select7();
int select5_ifno(string[],string[],int[]);
int select8();
string select5_ifyes(string[],string[],int[],int*);
string account[16],password[16], phonenumber[16];
int loginstatus[16]={0},numberofaccount=0;
int main()
{
    int state=0;
    int option;
    int status[15] = {0};
    string username;

    while (true)
    {
        cout << "*** Welcome to NCU theater reservation system ***" << endl;
         if(state==1)cout<<"***Welcome back "<<username<<"***"<<endl;
         cout<< "Please type 1 to make a new reservation" << endl
         << "Please type 2 to cancel an existing reservation" << endl
         << "Please type 3 to show the all available seats" << endl
         << "Please type 4 to show the status of all current seats" << endl;
         if(state==0)cout<< "Please type 5 to member center" << endl;
         else cout<<"Please type 5 to log-out"<<endl;
         cout<< "Please type 6 to show member"<<endl;
         cout<<"Please type 7 to load member information"<<endl;
         cout<<"Please type 8 to change member data"<<endl;
         cout<<"Please type 9 to exit the system"<<endl;
         cout<< "Enter your selection Here: ";
        (cin>> option).get();
        while(option < 1 || option> 9)
        {
            cout << "Invalid input, please enter your selection again: ";
           (cin>> option).get();
        }
        cout << endl;
        if(option == 1)
        {
            char ans;
            cout << "***Make a new reservation***" << endl;
            cout << "Do you need a specified seat? (y/n) ";
            cin >> ans;
            while(ans != 'y' && ans != 'n')
            {
                cout << "Invalid input, please enter your selection again: ";
                cin >> ans;
            }
            if(ans == 'y')
            {
                int number;
                cout << "Enter the seat number: ";
                cin >> number;
                while(number < 1 || number > 15)
                {
                    cout << "Invalid input, please enter your selection again: ";
                    cin >> number;
                }
                while(status[number -1] == 1 )
                {
                    cout << "The seat has been reserved, please enter your selection again: ";
                    cin >> number;
                }
                status[number - 1] = 1;
                cout << "The seat number " << number << " is reserved for you..." << endl << endl;
            }
            else
            {
                for(int n = 0; n < 15; n++)
                {
                    if(status[n] == 0)
                    {
                        status[n] = 1;
                        cout << "The seat number " << n+1 << " is reserved for you..." << endl << endl;
                        break;
                    }
                }
            }
        }

        if(option == 2)
        {
            int cancel;
            cout << "***Cancel an existing reservation***" << endl;
            cout << "Please enter the seat number which you want to cancel: ";
            cin >> cancel;
            if(status[cancel - 1] == 1)
            {
                status[cancel - 1] = 0;
                cout << "The seat number " << cancel << " is available now..." << endl << endl;
            }
            else   cout << "The seat is not reserved" << endl << endl;
        }

        if(option == 3)
        {
            cout << "***Show the all available seats***" << endl;
            for(int i = 0; i < 15; i++)
            {
                if(status[i] == 0)cout << "seat " << i+1<< endl;
            }
            cout << endl;
        }

        if(option == 4)
        {
            cout << "***Show the status of all seats***" << endl;
            cout << "Seat number       Status" << endl;
            for(int i = 0; i < 15; i++)
            {
                cout << "Seat " << setw(13) << left <<  i+1;
                if(status[i] == 0)cout << "available" << endl;
                else cout << "reserved" << endl;
            }
            cout << endl;
        }

        if(option==5&&state==1)state=0;
        else if(option==5&&state==0)state=select5(username);
        if(option == 6)
        {
            cout<<"***NCU Theater Membership***"<<endl;

            if(numberofaccount<1)cout<<"No Member."<<endl<<endl;
            else
            {
            cout<<"No.  Username"<<endl;
            for(int i=0;i<numberofaccount;i++)cout<<i+1<<left<<setw(4-(i+1)/10)<<"."<<account[i]<<endl;
            cout<<endl;
            }
        }
        if(option==7)select7();
        if(option==8)select8();
        if(option==9)
        {
            state=0;
            cout << "Thank you for using our system" << endl;
            cout << "Have a nice day~~";
            return 0;
        }
    }
}
int select5(string &username)
{
    int a=0;
    char select[3];
   cout<<"***NCU Theater Member Center***"<<endl;

    cout << "Do you have the membership? (y/n) ";
    cin.getline(select,2);
    if(select[0]=='y'){username=select5_ifyes(account,password,loginstatus,&a);}
    else select5_ifno(account,password,loginstatus);

    return a;
}

string select5_ifyes(string account[16],string password[16],int loginstatus[16],int *a)
{
    int state=0;
    string username,userpassword,null;
    int name=0,pass=0;

    cout<<"Enter Username: ";
    getline(cin,username);
    cout<<"Enter Password: ";
    getline(cin,userpassword);

    for(int i=0;i<16;i++)
    {
        if(username==account[i])name=1;
    }
    for(int i=0;i<16;i++)
    {
        if(userpassword==password[i]) pass=1;
    }

 if(pass==1&&name==1){cout<<endl;*a=1;return username;}
 else cout<<"The username and the password don't match."<<endl<<endl;

}
int select5_ifno(string account[16],string password[16],int loginstatus[16])
{
    char select[3];
    cout<<"Would you like to sign up? (y/n) ";
    cin.getline(select,2);
    if(select[0]=='y')
    {
        int state=0;
        while(loginstatus[state]==1)state++;
        cout<<"Enter Username: ";
        getline(cin,account[state]);
        cout<<"Enter Password: ";
        getline(cin,password[state]);
        cout<<"Enter Phone number: ";
        getline(cin,phonenumber[state]);
        loginstatus[state]=1;
        cout<<"Welcome! You are now a member of NCU theater.\nPlease log in again."<<endl<<endl;
        numberofaccount++;
    }
    else cout<<"Okay! Have a nice day."<<endl<<endl;
}
int select7()
{

        string infilename;
        cout<<"***Load member information***"<<endl;
        cout << "Please enter the member file name: ";
        cin>>infilename;
        ifstream ifile(infilename,ios::in);
        if(ifile.is_open())
        {
             cout<<"The file "<<infilename<<" has been loaded..."<<endl<<endl;
             while(!ifile.eof())
            {
                string a;
                ifile>>a;
                if(a=="Phone")break;
            }
            int state=0;
            while(loginstatus[state]==1)state++;
            while(!ifile.eof())
            {
            ifile>>account[state];
            ifile>>password[state];
            ifile>>phonenumber[state];
            loginstatus[state]=1;
            state++;
            numberofaccount++;
            }
            ifile.close();
        }

        else cout<<"File could not be opened."<<endl;
}
int select8()
{
    int select,name=0,pass=0,order;
    string username,userpassword,null;
    cout<<"***Change member data***"<<endl
        <<"Please type 1 to change password"<<endl
        <<"Please type 2 to change phone number"<<endl
        <<"Enter your selection Here: ";
    (cin>>select).get();
    cout<<"Enter Username: ";
    getline(cin,username);
    cout<<"Enter Password: ";
    getline(cin,userpassword);
    for(int i=0;i<16;i++)
    {
        if(username==account[i])name=1;
    }
    for(int i=0;i<16;i++)
    {
        if(userpassword==password[i]) pass=1;
        order=i;
    }
    if(pass==1&&name==1)
    {
        switch(select)
        {
        case 1:
            {
                cout<<"Enter the new password: ";
                getline(cin,password[order]);
                break;
            }
        case 2:
            {
                cout<<"Enter the new phone number: ";
                getline(cin,phonenumber[order]);
                break;
            }
        default:break;
        }
    }
    else cout<<"The username and the password don't match."<<endl;
    cout<<endl;

}
