#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
struct information
{
    string name;
    string password;
    string phone_number;
};
void show_welcome(string);

void make_reservation(vector<int> &, int number = 15);

void cancel_reservation(vector<int> &, int number = 15);

void show_available(vector<int> &, int number = 15);

void show_status(vector<int> &, int number = 15);

void member_center(information []);

void show_member(information []);

void load_member_information(information []);
void change_member_data(information []);

void find_member_data(information []);

string log_in_name="0";

int main()
{
    int control;
    vector<int> seat(16);
    information member[16];
    for(int i=1;i<=15;i++)
    {
        member[i].name="0";
        member[i].password="0";
        member[i].phone_number="0";
    }


    while (true)
    {
        show_welcome(log_in_name);
            (cin >> control).get();
            if (control >= 10 || control < 1)
                if (control == 10)
                {
                    cout << "\nThank you for using our system\nHave a nice day~~";
                    break;
                }

                else
                {
                    do
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "Invalid input, please enter your selection again: ";
                        (cin >> control).get();


                        if (control == 10)
                        {
                            cout << "Thank you for using our system\nHave a nice day~~";
                            return 0;
                        }
                    } while (control > 10 || control < 1);

                }




        switch (control)
        {
        case 1:
            make_reservation(seat);
            break;

        case 2:
            cancel_reservation(seat);
            break;

        case 3:
            show_available(seat);
            break;

        case 4:
            show_status(seat);
            break;

        case 5:
            if(log_in_name=="0")
                member_center(member);
            else                  //log out
            {
                 cout<<endl;
                log_in_name="0";
            }

            break;

        case 6:
            show_member(member);
            break;

        case 7:
            load_member_information(member);
            break;
        case 8:
            change_member_data(member);
            break;
        case 9:
            find_member_data(member);
            break;

        }
    }
}
void show_welcome(string name)
{
    if(name=="0")
    {
        cout << "*** Welcome to NCU theater reservation system ***" << endl;
        cout << "Please type 1 to make a new reservation" << endl;
        cout << "Please type 2 to cancel an existing reservation" << endl;
        cout << "Please type 3 to show the all available seats" << endl;
        cout << "Please type 4 to show the status of all current seats" << endl;
        cout << "Please type 5 to member center" <<  endl;
        cout << "Please type 6 to show member" << endl;
        cout << "Please type 7 to load member information" << endl;
        cout << "Please type 8 to change member data"<<endl;
        cout << "Please type 9 to find member data"<<endl;
        cout<<"Please type 10 to exit the system"<<endl;
        cout << "Enter your selection Here: ";
    }
    else
    {
        cout << "*** Welcome to NCU theater reservation system ***" << endl;
        cout << "***Welcome back "<< name <<"***"<<endl;
        cout << "Please type 1 to make a new reservation" << endl;
        cout << "Please type 2 to cancel an existing reservation" << endl;
        cout << "Please type 3 to show the all available seats" << endl;
        cout << "Please type 4 to show the status of all current seats" << endl;
        cout << "Please type 5 to log-out" << endl;
        cout << "Please type 6 to show member" << endl;
        cout << "Please type 7 to load member information" << endl;
        cout << "Please type 8 to change member data"<<endl;
        cout << "Please type 9 to find member data"<<endl;
        cout<<"Please type 10 to exit the system"<<endl;
        cout << "Enter your selection Here: ";
    }

    return;
}

void make_reservation(vector<int> &seat, int number)
{
    cout << "\n***Make a new reservation***" << endl;
    string yn;
    int seat_number;
    cout << "Do you need a specified seat? (y/n) ";
    (cin >> yn).get();

    while (yn != "y" && yn != "n")
    {
        cout << "Invalid input, please enter your selection again: ";
        (cin >> yn).get();
    }

    if (yn == "y")
    {

        cout << "Enter the seat number: ";
        cin >> seat_number;

        while (seat_number < 1 || seat_number > 15)
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid input, please enter your selection again: ";
            cin >> seat_number;
        }

        if (seat[seat_number] == 0)
        {
            seat[seat_number] = 1;
            cout << "The seat number " << seat_number << " is reserved for you..." << endl << endl;
        }
         else
        {
            do
            {

                cout << "The seat has been reserved, please enter your selection again: ";
                cin >> seat_number;

                while (seat_number < 1 || seat_number > 15)
                {
                     cin.clear();
                     cin.ignore();
                    cout << "Invalid input, please enter your selection again: ";
                    cin >> seat_number;
                }
            } while (seat[seat_number] == 1);

            seat[seat_number] = 1;
            cout << "The seat number " << seat_number << " is reserved for you..." << endl << endl;
        }
    }
     else
    {
        for (int i = 1; i <= number; i++)
         {
            if (seat[i] == 0)
            {
                seat[i] = 1;
                cout << "The seat number " << i << " is reserved for you..." << endl << endl;
                break;
            }

        }

    }



}
void cancel_reservation(vector<int> &seat, int number)
{
    cout << "\n***Cancel an existing reservation***" << endl;
    int seat_number;
    cout << "Please enter the seat number which you want to cancel: ";
    cin >> seat_number;

    while (seat_number < 1 || seat_number > 15)
    {
        cin.clear();
        cin.ignore();
        cout << "Invalid input, please enter your selection again: ";
        cin >> seat_number;
    }

    if (seat[seat_number] == 0)
        cout << "The seat is not reserved" << endl << endl;
    else
    {
        seat[seat_number] = 0;
        cout << "The seat number " << seat_number << " is available now..." << endl << endl;
    }

}
void show_available(vector<int> &seat, int number) {
    cout << "\n***Show the all available seats***" << endl;

    for (int i = 1; i <= number; i++)
    {
        if (seat[i] == 0)
            cout << "seat " << i << endl;
    }

    cout << endl;
}
void show_status(vector<int> &seat, int number)
{
    cout << "\n***Show the status of all seats***" << endl;
    cout << "Seat number       Status" << endl;

    for (int i = 1; i <= number; i++)
    {
        cout << "Seat " << setw(13) << left << i;

        if (seat[i] == 0)
            cout << "available" << endl;
        else
            cout << "reserved" << endl;


    }

    cout << endl;
}
void member_center(information member[])
{
    string membership,sign_member;
    string username,user_password,user_phone_number;
    int name_index=0;

    cout<<"\n***NCU Theater Member Center***" <<endl;
    cout<<"Do you have the membership? (y/n) ";
        (cin >> membership).get();

        while (membership != "y" && membership != "n")
        {
            cout << "Invalid input, please enter your selection again: ";
            (cin >> membership).get();
        }
    if(membership=="y")
    {
        cout<<"Enter Username: ";
        getline(cin,username);
        cout<<"Enter Password: ";
        getline(cin,user_password);
        for(int i=1;i<=15;i++)
        {
            if(username==member[i].name)
            {
                name_index=i;
            }

        }
        if(name_index!=0)
        {
            if(user_password==member[name_index].password)
            {
                log_in_name=member[name_index].name;

            }
            else
                cout<<"The username and the password don't match."<<endl;
        }

        else
            cout<<"The username and the password don't match."<<endl;
    }   //end if
    else   // membership   =  n
    {
        cout<<"Would you like to sign up? (y/n) ";
            (cin>>sign_member).get();
            while (sign_member != "y" && sign_member != "n")
            {
                cout << "Invalid input, please enter your selection again: ";
                (cin >> sign_member).get();
            }
        if(sign_member=="y")
        {
            cout<<"Enter Username: ";
            getline(cin,username);
            cout<<"Enter Password: ";
            getline(cin,user_password);
            cout<<"Enter Phone number: ";
            getline(cin,user_phone_number);
            for(int i=1;i<=15;i++)
            {
                if(member[i].name=="0")
                {
                    member[i].name=username;
                    member[i].password=user_password;
                    member[i].phone_number=user_phone_number;
                    break;
                }
            }
            cout<<"Welcome! You are now a member of NCU theater.\nPlease log in again."<<endl;

        }
        else //sign_member==n
        {
            cout<<"Okay! Have a nice day."<<endl;
        }
    }

    cout<<endl;


}
void show_member(information member[])
{
    cout<<"\n***NCU Theater Membership***"<<endl;
    int width;
    if(member[1].name=="0")
        cout<<"No Member."<<endl;
    else
    {
        cout<<"No.  Username"<<endl;
        for(int i=1;i<=15;i++)
        {
            if(i>=10)
                width=3;
            else
                width=4;
            if(member[i].name!="0")
            cout<<i<<left<<setw(width)<<"."<<member[i].name<<endl;
        }
    }
    cout<<endl;
}
void load_member_information(information member[])
{
    cout<<"\n***Load member information***"<<endl;
    string filename;

    cout<<"Please enter the member file name: ";
    cin >> filename;
    fstream inputfile(filename,ios::in);
    if(!inputfile)
    {
        cout << "File could not be opened. "<<endl<<endl;
        return ;
    }
    cout<<"The file "<<filename<<" has been loaded..."<<endl;
    string garbage;
    inputfile>>garbage>>garbage>>garbage;
    int index=0;
    for(int i=1;i<=15;i++)
    {
        if(member[i].name!="0")
        {
            index=i;
            break;
        }
    }
    while(inputfile>>member[++index].name>>member[index].password>>member[index].phone_number)
    {   }









    cout<<endl;
    return;

}
void change_member_data(information member[])
{
   cout<<"\n***Change member data***"<<endl;
   cout<<"Please type 1 to change password"<<endl;
   cout<<"Please type 2 to change phone number"<<endl;
   cout<<"Enter your selection Here: ";
   int control;
   (cin>>control).get();
   while(control!=1&&control!=2)
   {
        cin.clear();
        cin.ignore();
        cout << "Invalid input, please enter your selection again: ";
       (cin >> control).get();
   }
   //改動資料
   string username,user_password,user_phone_number;
   int name_index=0;
   cout<<"Enter Username: ";
   getline(cin,username);
   cout<<"Enter Password: ";
   getline(cin,user_password);
   for(int i=1;i<=15;i++)
    {
        if(username==member[i].name)
        {
            name_index=i;
        }

    }
    if(name_index==0)  //名字incorrect
    {
        cout<<"The username and the password don't match."<<endl;
        cout<<endl;
        return;
    }
    else if(member[name_index].password!=user_password)  //密碼incorrect
    {
        cout<<"The username and the password don't match."<<endl;
        cout<<endl;
        return;
    }
    if(control==1)   // change 密碼
    {
        cout<<"Enter the new password: ";
        getline(cin,user_password);
        member[name_index].password=user_password;
    }
    else   // change phone number
    {
        cout<<"Enter the new phone number: ";
        getline(cin,user_phone_number);
        member[name_index].phone_number=user_phone_number;
    }
     cout<<endl;

}
void find_member_data(information member[])
{
    cout<<"\n***Find member data***"<<endl;
    cout<<"Please enter the search keyword: ";
    string search_name;

    getline(cin,search_name);
    cout<<"The searching keyword is \""<<search_name<<"\"..."<<endl<<endl;
    bool flag=true,flag2=false;
    vector <int> member_index;
    for(int i=1;i<=15;i++)
    {

        for(int j=0;j<member[i].name.length();j++)
        {
            flag=false;
            if(member[i].name[j]==search_name[0])
            {   flag=true;
                for(int k=0;k<search_name.length();k++)
                {
                    if(search_name[k]!=member[i].name[j+k])
                    {
                        flag=false;
                        break;
                    }

                }
            }
            if(flag==true)
            {
                flag2=true;
                member_index.push_back(i);
                break;
            }

        }


    }
    if(flag2==true)
    {
        cout<<"The searching results are as follows:"<<endl;
        cout<<"*** Customer Information ***"<<endl;
        cout<<"Name       Password       Phone"<<endl;
       for(int i=0;i<member_index.size();i++)
       {
           cout<<left<<setw(11)<<member[member_index[i]].name<<setw(8)<<member[member_index[i]].password<<"       "<<setw(10)<<member[member_index[i]].phone_number<<endl;
       }
    }
    else if(flag2==0)
    {
        cout<<"\nWe cannot find the keyword."<<endl;
    }
    cout<<endl;

}





