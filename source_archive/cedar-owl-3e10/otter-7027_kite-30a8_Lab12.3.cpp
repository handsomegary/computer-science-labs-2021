#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

void show_welcome(string);

void make_reservation(vector<int> &, int number = 15);

void cancel_reservation(vector<int> &, int number = 15);

void show_available(vector<int> &, int number = 15);

void show_status(vector<int> &, int number = 15);

void member(string [],string []);

void show_member(string []);

void load_member_information(string [],string []);

string log_in_name="0";     //°O¿ý½Ölog in
int main()
{
    int control;
    vector<int> seat(16);
    string name[16]={"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};
    string password[16]={"0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"};

    while (true)
    {
        show_welcome(log_in_name);
            cin >> control;
            if (control >= 8 || control < 1)
                if (control == 8)
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
                        cin >> control;


                        if (control == 8)
                        {
                            cout << "Thank you for using our system\nHave a nice day~~";
                            return 0;
                        }
                    } while (control > 8 || control < 1);

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
                member(name,password);
            else                  //log out
            {
                 cout<<endl;
                log_in_name="0";
            }

            break;

        case 6:
            show_member(name);
            break;

        case 7:
            load_member_information(name,password);
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
        cout << "Please type 8 to exit the system"<<endl;
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
        cout << "Please type 8 to exit the system"<<endl;
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
void member(string name[],string password[])
{
    string membership,sign_member;
    string username,user_password;
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
            if(username==name[i])
            {
                name_index=i;
            }

        }
        if(name_index!=0)
        {
            if(user_password==password[name_index])
            {
                log_in_name=name[name_index];

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
            for(int i=1;i<=15;i++)
            {
                if(name[i]=="0")
                {
                    name[i]=username;
                    password[i]=user_password;
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
void show_member(string name[])
{
    cout<<"\n***NCU Theater Membership***"<<endl;
    int width;
    if(name[1]=="0")
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
            if(name[i]!="0")
            cout<<i<<left<<setw(width)<<"."<<name[i]<<endl;
        }
    }
    cout<<endl;
}
void load_member_information(string name[],string password[])
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
    inputfile>>garbage>>garbage;
    int index=0;
    for(int i=1;i<=15;i++)
    {
        if(name[i]!="0")
        {
            index=i;
            break;
        }
    }
    while(inputfile>>name[++index]>>password[index])
    {   }









    cout<<endl;
    return;

}
