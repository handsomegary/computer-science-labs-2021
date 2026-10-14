#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

int main() {
    long long int input;
    char yn;
    int array[16] = { 0 };
    int seatnumber;
    while (1) {
        cout << "*** Welcome to NCU theater reservation system ***" << endl;
        cout << "Please type 1 to make a new reservation" << endl;
        cout << "Please type 2 to cancel an existing reservation" << endl;
        cout << "Please type 3 to show the all available seats" << endl;
        cout << "Please type 4 to show the status of all current seats" << endl;
        cout << "Please type 5 to exit the system" << endl;
        cout << "Enter your selection Here: ";
    here:
        cin >> input;
        if (input == 1) {
            cout << endl << "***Make a new reservation***" << endl;
            cout << "Do you need a specified seat? (y/n) ";
        here3:
            cin >> yn;
            if (yn != 'y' && yn != 'n') {
                cout << "Invalid input, please enter your selection again: ";
                goto here3;
            }
            if (yn == 'y') {
                cout << "Enter the seat number: ";
                while (1) {
                here2:
                    cin >> seatnumber;
                    if (seatnumber > 15 || seatnumber < 1) {
                        cout << "Invalid input, please enter your selection again: ";
                        goto here2;
                    }
                    if (array[seatnumber] == 0) {
                        cout << "The seat number " << seatnumber << " is reserved for you..." << endl << endl;
                        array[seatnumber] = 1;
                        break;
                    }
                    else {
                        cout << "The seat has been reserved, please enter your selection again: ";
                    }
                }
            }
            if (yn == 'n') {
                for (int i = 1;i <= 15;i++) {
                    if (array[i] == 0) {
                        cout << "The seat number " << i << " is reserved for you...";
                        array[i] = 1;
                        break;
                    }
                }
                cout << endl << endl;
            }
        }
        if (input == 2) {
            cout << endl << "***Cancel an existing reservation***" << endl << "Please enter the seat number which you want to cancel: ";
            cin >> seatnumber;
            if (array[seatnumber] == 0) {
                cout << "The seat is not reserved" << endl << endl;
            }
            if (array[seatnumber] != 0) {
                cout << "The seat number " << seatnumber << " is available now..." << endl << endl;
                array[seatnumber] = 0;
            }
        }
        if (input == 3) {
            cout << endl << "***Show the all available seats***" << endl;
            for (int i = 1;i <= 15;i++) {
                if (array[i] == 0) {
                    cout << "seat " << i << endl;
                }
                else {
                    continue;
                }
            }
            cout << endl;
        }
        if (input == 4) {
            cout << endl << "***Show the status of all seats***" << endl;
            cout << "Seat number       Status" << endl;
            for (int i = 1; i <= 15;i++) {
                if (array[i] == 0 && i < 10) {
                    cout << "Seat " << i << "            " << "available" << endl;
                }
                if (array[i] != 0 && i < 10) {
                    cout << "Seat " << i << "            " << "reserved" << endl;
                }
                if (array[i] == 0 && i >= 10) {
                    cout << "Seat " << i << "           " << "available" << endl;
                }
                if (array[i] != 0 && i >= 10) {
                    cout << "Seat " << i << "           " << "reserved" << endl;
                }
            }
            cout << endl;
        }
        if (input == 5) {
            cout << endl << "Thank you for using our system" << endl << "Have a nice day~~";
            break;
        }
        if (input > 5 || input < 1) {
            cout << "Invalid input, please enter your selection again: ";
            goto here;
        }
    }
}