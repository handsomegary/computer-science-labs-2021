#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool readInteger(int &value, int low, int high) {
    string token;
    while (cin >> token) {
        istringstream input(token);
        if ((input >> value) && input.peek() == char_traits<char>::eof() && value >= low && value <= high) return true;
        cout << "Invalid input, please enter your selection again: ";
    }
    return false;
}
bool readAnswer(char &answer) {
    string token;
    while (cin >> token) {
        if (token == "y" || token == "n") {
            answer = token[0];
            return true;
        }
        cout << "Invalid input, please enter your selection again: ";
    }
    return false;
}
int firstAvailable(const bool (&reserved)[15]) {
    for (int i = 0; i < 15; ++i) if (!reserved[i]) return i;
    return -1;
}

int main() {
    bool reserved[15] = {};
    int option;
    while (true) {
        cout << "*** Welcome to NCU theater reservation system ***\n"
             << "Please type 1 to make a new reservation\n"
             << "Please type 2 to cancel an existing reservation\n"
             << "Please type 3 to show the all available seats\n"
             << "Please type 4 to show the status of all current seats\n"
             << "Please type 5 to exit the system\n"
             << "Enter your selection Here: ";
        if (!readInteger(option, 1, 5)) return 0;
        cout << '\n';
        if (option == 1) {
            cout << "***Make a new reservation***\n";
            if (firstAvailable(reserved) == -1) {
                cout << "All seats have been reserved\n\n";
                continue;
            }
            char answer;
            cout << "Do you need a specified seat? (y/n) ";
            if (!readAnswer(answer)) return 0;
            int index = firstAvailable(reserved);
            if (answer == 'y') {
                int seat;
                cout << "Enter the seat number: ";
                while (true) {
                    if (!readInteger(seat, 1, 15)) return 0;
                    if (!reserved[seat - 1]) { index = seat - 1; break; }
                    cout << "The seat has been reserved, please enter your selection again: ";
                }
            }
            reserved[index] = true;
            cout << "The seat number " << index + 1 << " is reserved for you...\n\n";
        } else if (option == 2) {
            int seat;
            cout << "***Cancel an existing reservation***\n"
                 << "Please enter the seat number which you want to cancel: ";
            if (!readInteger(seat, 1, 15)) return 0;
            if (reserved[seat - 1]) {
                reserved[seat - 1] = false;
                cout << "The seat number " << seat << " is available now...\n\n";
            } else cout << "The seat is not reserved\n\n";
        } else if (option == 3) {
            cout << "***Show the all available seats***\n";
            for (int i = 0; i < 15; ++i) if (!reserved[i]) cout << "seat " << i + 1 << '\n';
            cout << '\n';
        } else if (option == 4) {
            cout << "***Show the status of all seats***\nSeat number       Status\n";
            for (int i = 0; i < 15; ++i)
                cout << "Seat " << left << setw(13) << i + 1 << (reserved[i] ? "reserved" : "available") << '\n';
            cout << '\n';
        } else {
            cout << "Thank you for using our system\nHave a nice day~~\n";
            return 0;
        }
    }
}
