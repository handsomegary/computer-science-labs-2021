#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;

void Member(char *membership, int *seat[15], char *seatstatus[15]);
int main()
{
    int option, seat[15]= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    char seatstatus[15] = {'a','a','a','a','a','a','a','a','a','a','a','a','a','a','a'};
    while (true)
    {
        cout << "*** Welcome to NCU theater reservation system ***" << endl;
        cout << "Please type 1 to make a new reservation" << endl;
        cout << "Please type 2 to cancel an existing reservation" << endl;
        cout << "Please type 3 to show the all available seats" << endl;
        cout << "Please type 4 to show the status of all current seats" << endl;
        cout << "Please type 5 to the member center" << endl;
        cout << "Please type 6 to exit the system" << endl;
        cout << "Enter your selection Here: ";
        cin >> option;
        while(option < 1 || option > 6)
        {
            cout << "Invalid input, please enter your selection again: ";
            cin >> option;
        }
        cout << endl;
        if(option == 1)
        {
            char answer;
            cout << "***Make a new reservation***" << endl;
            cout << "Do you need a specified seat? (y/n) ";
            cin >> answer;
            while(answer != 'y' && answer != 'n')
            {
                cout << "Invalid input, please enter your selection again: ";
                cin >> answer;
            }
            if(answer == 'y')
            {
                int seatnumber;
                cout << "Enter the seat number: ";
                cin >> seatnumber;
                while(seatnumber < 1 || seatnumber > 15)
                {
                    cout << "Invalid input, please enter your selection again: ";
                    cin >> seatnumber;
                }
                while(seatstatus[seatnumber -1] == 'r' )
                {
                    cout << "The seat has been reserved, please enter your selection again: ";
                    cin >> seatnumber;
                }
                seatstatus[seatnumber - 1] = 'r';
                cout << "The seat number " << seatnumber << " is reserved for you..." << endl << endl;
            }
            else if(answer == 'n')
            {
                for(int n = 0; n < 15; n++)
                {
                    if(seatstatus[n] == 'a')
                    {
                        seatstatus[n] = 'r';
                        cout << "The seat number " << n+1 << " is reserved for you..." << endl << endl;
                        break;
                    }
                }
            }
        }
        else{}
        if(option == 2)
        {
            int cancelseat;
            cout << "***Cancel an existing reservation***" << endl;
            cout << "Please enter the seat number which you want to cancel: ";
            cin >> cancelseat;
            if(seatstatus[cancelseat - 1] == 'r')
            {
                seatstatus[cancelseat - 1] = 'a';
                cout << "The seat number " << cancelseat << " is available now..." << endl << endl;
            }
            else if(seatstatus[cancelseat - 1] == 'a')
            {
                cout << "The seat is not reserved" << endl << endl;
            }
            else{}

        }
        else{}
        if(option == 3)
        {
            cout << "***Show the all available seats***" << endl;
            for(int i = 0; i < 15; i++)
            {
                if(seatstatus[i] == 'a')
                {
                    cout << "seat " << seat[i] << endl;
                }
            }
            cout << endl;
        }
        else{}
        if(option == 4)
        {
            cout << "***Show the status of all seats***" << endl;
            cout << "Seat number       Status" << endl;
            for(int j = 0; j < 15; j++)
            {
                cout << "Seat " << setw(13) << left <<  seat[j];
                if(seatstatus[j] == 'a')
                {
                    cout << "available" << endl;
                }
                else if(seatstatus[j] == 'r')
                {
                    cout << "reserved" << endl;
                }
                else{}
            }
            cout << endl;
        }
        else{}
        if(option == 5)
        {
            char membership, signup;
            cout << "***NCU Theater Member Center***" << endl;
            cout << "Do you have the membership? (y/n) ";
            cin >> membership;
            if(membership == 'y')
            {
                Member('y', seat[15], seatstatus[15]);
            }
            else if(membership == 'n')
            {
                cout << "Would you like to sign up? (y/n) ";
                cin >> signup;
                if(signup == 'y')
                {
                    Member('y', seat[15], seatstatus[15]);
                }
                else if(signup == 'n')
                {
                    cout << "Okay! Have a nice day." << endl << endl;
                }
            }

        }
        if(option == 6)
        {
            cout << "Thank you for using our system" << endl;
            cout << "Have a nice day~~";
            return 0;
        }
    }
}
void Member(char *membership, int *seat[15], char *seatstatus[15])
{
    string username, password;
    char str_arr[100][15] = {'\n'};
    if(membership == 'y')
    {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
    }
    else if(membership == 'n');
    {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Welcome! You are now a member of NCU theater." << endl << "Please log in again.";
    }
}
