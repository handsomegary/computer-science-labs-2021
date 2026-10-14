#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

void show_welcome();

void make_reservation(vector<int> &, int number = 15);

void cancel_reservation(vector<int> &, int number = 15);

void show_available(vector<int> &, int number = 15);

void show_status(vector<int> &, int number = 15);

int main()
{
    int control;
    vector<int> seat(16);

    while (true)
    {
        show_welcome();
        cin >> control;

        if (control >= 5 || control < 1)
            if (control == 5)
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


                    if (control == 5)
                    {
                        cout << "Thank you for using our system\nHave a nice day~~";
                        return 0;
                    }
                } while (control > 5 || control < 1);

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
        }
    }
}
void show_welcome()
{
    cout << "*** Welcome to NCU theater reservation system ***" << endl;
    cout << "Please type 1 to make a new reservation" << endl;
    cout << "Please type 2 to cancel an existing reservation" << endl;
    cout << "Please type 3 to show the all available seats" << endl;
    cout << "Please type 4 to show the status of all current seats" << endl;
    cout << "Please type 5 to exit the system" << endl;
    cout << "Enter your selection Here: ";
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
