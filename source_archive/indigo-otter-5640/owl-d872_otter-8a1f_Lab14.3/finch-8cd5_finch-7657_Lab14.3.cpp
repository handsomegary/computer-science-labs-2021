#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void changedata(string usernamearray[], string passwordarray[], string phonenumberarray[]) {
    string username;
    string password;
    string phonenumber;
    int choice = 0;
    cout << "\n***Change member data***" << endl;
    cout << "Please type 1 to change password\nPlease type 2 to change phone number\nEnter your selection Here: ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        int y = 0;
        for (int x = 0; x < 100;x++) {
            if (usernamearray[x] == username) {
                if (passwordarray[x] == password) {
                    y = 1;
                    cout << "Enter the new password: ";
                    cin >> password;
                    passwordarray[x] = password;
                    cout << endl;
                    break;
                }
                if (passwordarray[x] != password) {
                    break;
                }
            }
        }
        if (y == 0) {
            cout << "The username and the password don't match." << endl << endl;
        }
    }
    if (choice == 2) {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        int y = 0;
        for (int x = 0; x < 100;x++) {
            if (usernamearray[x] == username) {
                if (passwordarray[x] == password) {
                    y = 1;
                    cout << "Enter the new phone number: ";
                    cin >> phonenumber;
                    phonenumberarray[x] = phonenumber;
                    cout << endl;
                    break;
                }
                if (passwordarray[x] != password) {
                    break;
                }
            }
        }
        if (y == 0) {
            cout << "The username and the password don't match." << endl << endl;
        }
    }
}

void Member(string usernamearray[], string passwordarray[], string phonenumberarray[], long long int& x) {
    string username1;
    string password1;
    string phonenumber1;
    cout << "Enter Username: ";
    cin >> username1;
    usernamearray[x] = username1;
    cout << "Enter Password: ";
    cin >> password1;
    passwordarray[x] = password1;
    cout << "Enter Phone number: ";
    cin >> phonenumber1;
    phonenumberarray[x] = phonenumber1;
    x++;
    cout << "Welcome! You are now a member of NCU theater." << endl;
    cout << "Please log in again." << endl << endl;
}
void Memberlogin(string usernamearray[], string passwordarray[], string username, string password, int& tf) {
    int y = 0;
    for (int x = 0; x < 100;x++) {
        if (usernamearray[x] == username) {
            if (passwordarray[x] == password) {
                tf = 2;
                y = 1;
                cout << endl;
                break;
            }
            if (passwordarray[x] != password) {
                break;
            }
        }
    }
    if (y == 0) {
        cout << "The username and the password don't match." << endl << endl;
    }
}
int main() {
    long long int input;
    long long int x = 0;
    char yn;
    int tf = 1;
    int array[16] = { 0 };
    int seatnumber;
    int serachcounter = 0;
    string search;
    string txt;
    string username;
    string password;
    string phonenumber;
    string usernamearray[100];
    string passwordarray[100];
    string phonenumberarray[100];
    while (1) {
        while (tf == 1) {
            cout << "*** Welcome to NCU theater reservation system ***" << endl;
            cout << "Please type 1 to make a new reservation" << endl;
            cout << "Please type 2 to cancel an existing reservation" << endl;
            cout << "Please type 3 to show the all available seats" << endl;
            cout << "Please type 4 to show the status of all current seats" << endl;
            cout << "Please type 5 to member center" << endl;
            cout << "Please type 6 to show member" << endl;
            cout << "Please type 7 to load member information" << endl;
            cout << "Please type 8 to change member data" << endl;
            cout << "Please type 9 to find member data" << endl;
            cout << "Please type 10 to exit the system" << endl;
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
                cout << endl << "***NCU Theater Member Center***" << endl;
                cout << "Do you have the membership? (y/n) ";
            here7:
                cin >> yn;
                if (yn != 'y' && yn != 'n') {
                    cout << "Invalid input, please enter your selection again: ";
                    goto here7;
                }
                if (yn == 'n') {
                    cout << "Would you like to sign up? (y/n) ";
                here8:
                    cin >> yn;
                    if (yn != 'y' && yn != 'n') {
                        cout << "Invalid input, please enter your selection again: ";
                        goto here8;
                    }
                    if (yn == 'y') {
                        Member(usernamearray, passwordarray, phonenumberarray, x);
                        continue;
                    }
                    if (yn == 'n') {
                        cout << "Okay! Have a nice day.";
                        cout << endl << endl;
                    }
                }
                if (yn == 'y') {
                    cout << "Enter Username: ";
                    cin >> username;
                    cout << "Enter Password: ";
                    cin >> password;
                    Memberlogin(usernamearray, passwordarray, username, password, tf);
                }
            }
            if (input == 6) {
                cout << endl << "***NCU Theater Membership***" << endl;
                if (x != 0) {
                    cout << "No." << "  " << "Username" << endl;
                    for (int i = 0;i < x;i++) {
                        if (i < 9) {
                            cout << i + 1 << "." << "   " << usernamearray[i] << endl;
                        }
                        if (i >= 9) {
                            cout << i + 1 << "." << "  " << usernamearray[i] << endl;
                        }
                    }
                }
                if (x == 0) {
                    cout << "No Member." << endl;
                }
                cout << endl;
            }
            if (input == 7) {
                cout << endl << "***Load member information***" << endl;
                cout << "Please enter the member file name: ";
                cin >> txt;
                ifstream inClientFile(txt, ios::in);
                if (!inClientFile) {
                    cout << "File could not be opened." << endl << endl;
                    continue;
                }
                if (inClientFile) {
                    cout << "The file " << txt << " has been loaded..." << endl << endl;
                }
                inClientFile >> username >> password >> phonenumber;
                while (inClientFile >> username >> password >> phonenumber) {
                    usernamearray[x] = username;
                    passwordarray[x] = password;
                    phonenumberarray[x] = phonenumber;
                    x++;
                }
            }
            if (input == 8) {
                changedata(usernamearray, passwordarray, phonenumberarray);
            }
            if (input == 9) {
                cout << "\n***Find member data***\nPlease enter the search keyword: ";
                cin >> search;
                cout << "\nThe searching keyword is \"" << search << "\"..." << endl;
                for (int i = 0;i < x;i++) {
                    int k = usernamearray[i].find(search);
                    if (k != -1) {
                        serachcounter++;
                        if (serachcounter == 1) {
                            cout << "The searching results are as follows:\n";
                            cout << "*** Customer Information ***" << endl;
                            cout << "Name       Password       Phone" << endl;
                        }
                        cout << left << setw(11) << usernamearray[i] << setw(15) << passwordarray[i] << phonenumberarray[i] << endl;
                    }
                }
                if (serachcounter == 0) {
                    cout << "\nWe cannot find the keyword." << endl;
                }
                cout << endl;
                serachcounter = 0;
            }
            if (input == 10) {
                cout << endl << "Thank you for using our system" << endl << "Have a nice day~~";
                break;
            }
            if (input > 10 || input < 1) {
                cout << "Invalid input, please enter your selection again: ";
                goto here;
            }
        }
        while (tf == 2) {
            cout << "*** Welcome to NCU theater reservation system ***" << endl;
            cout << "***Welcome back " << username << "***" << endl;
            cout << "Please type 1 to make a new reservation" << endl;
            cout << "Please type 2 to cancel an existing reservation" << endl;
            cout << "Please type 3 to show the all available seats" << endl;
            cout << "Please type 4 to show the status of all current seats" << endl;
            cout << "Please type 5 to log-out" << endl;
            cout << "Please type 6 to show member" << endl;
            cout << "Please type 7 to load member information" << endl;
            cout << "Please type 8 to change member data" << endl;
            cout << "Please type 9 to find member data" << endl;
            cout << "Please type 10 to exit the system" << endl;
            cout << "Enter your selection Here: ";
        here4:
            cin >> input;
            if (input == 1) {
                cout << endl << "***Make a new reservation***" << endl;
                cout << "Do you need a specified seat? (y/n) ";
            here6:
                cin >> yn;
                if (yn != 'y' && yn != 'n') {
                    cout << "Invalid input, please enter your selection again: ";
                    goto here6;
                }
                if (yn == 'y') {
                    cout << "Enter the seat number: ";
                    while (1) {
                    here5:
                        cin >> seatnumber;
                        if (seatnumber > 15 || seatnumber < 1) {
                            cout << "Invalid input, please enter your selection again: ";
                            goto here5;
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
                tf = 1;
                cout << endl;
            }
            if (input == 6) {
                cout << endl << "***NCU Theater Membership***" << endl;
                cout << "No." << "  " << "Username" << endl;
                for (int i = 0;i < x;i++) {
                    if (i < 9) {
                        cout << i + 1 << "." << "   " << usernamearray[i] << endl;
                    }
                    if (i >= 9) {
                        cout << i + 1 << "." << "  " << usernamearray[i] << endl;
                    }
                }
                cout << endl;
            }
            if (input == 7) {
                cout << endl << "***Load member information***" << endl;
                cout << "Please enter the member file name: ";
                cin >> txt;
                ifstream inClientFile(txt, ios::in);
                if (!inClientFile) {
                    cout << "File could not be opened." << endl;
                    continue;
                }
                if (inClientFile) {
                    cout << "The file " << txt << " has been loaded..." << endl << endl;
                }
                inClientFile >> username >> password >> phonenumber;
                while (inClientFile >> username >> password >> phonenumber) {
                    usernamearray[x] = username;
                    passwordarray[x] = password;
                    phonenumberarray[x] = phonenumber;
                    x++;
                }
            }
            if (input == 8) {
                changedata(usernamearray, passwordarray, phonenumberarray);
            }
            if (input == 9) {
                cout << "\n***Find member data***\nPlease enter the search keyword: ";
                cin >> search;
                cout << "\nThe searching keyword is \"" << search << "\"..." << endl;
                for (int i = 0;i < x;i++) {
                    int k = usernamearray[i].find(search);
                    if (k != -1) {
                        serachcounter++;
                        if (serachcounter == 1) {
                            cout << "The searching results are as follows:\n";
                            cout << "*** Customer Information ***" << endl;
                            cout << "Name       Password       Phone" << endl;
                        }
                        cout << left << setw(11) << usernamearray[i] << setw(15) << passwordarray[i] << phonenumberarray[i] << endl;
                    }
                }
                if (serachcounter == 0) {
                    cout << "\nWe cannot find the keyword." << endl;
                }
                cout << endl;
                serachcounter = 0;
            }
            if (input == 10) {
                cout << endl << "Thank you for using our system" << endl << "Have a nice day~~";
                break;
            }
            if (input > 10 || input < 1) {
                cout << "Invalid input, please enter your selection again: ";
                goto here4;
            }
        }
        if (input == 10) {
            break;
        }
    }
}