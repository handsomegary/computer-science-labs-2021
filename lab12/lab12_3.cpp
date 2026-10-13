// Based on the original theater system; corrected for 2021 Lab 12.3.
// This translation unit is self-contained: submit or compile this .cpp alone.
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct MemberData { string username, password, phone; };
struct Theater {
    bool reserved[15];
    vector<MemberData> members;
    int logged_in;
    Theater() : reserved{}, logged_in(-1) {}
};
const char *invalid_input = "Invalid input, please enter your selection again: ";

bool read_integer(int& value, int minimum, int maximum) {
    string token;
    while (cin >> token) {
        istringstream parser(token);
        char extra;
        if (parser >> value && !(parser >> extra) && value >= minimum && value <= maximum) return true;
        cout << invalid_input;
    }
    return false;
}
bool read_yes_no(char& answer) {
    string token;
    while (cin >> token) {
        if (token == "y" || token == "n") { answer = token[0]; return true; }
        cout << invalid_input;
    }
    return false;
}
bool read_text(string& value, bool limited = true) {
    while (getline(cin >> ws, value)) {
        if (!value.empty() && (!limited || value.size() <= 50)) return true;
        cout << invalid_input;
    }
    return false;
}
int authenticate(const Theater& theater, const string& username, const string& password) {
    for (size_t i = 0; i < theater.members.size(); ++i)
        if (theater.members[i].username == username && theater.members[i].password == password)
            return static_cast<int>(i);
    return -1;
}
void Member(Theater& theater) {
    cout << "***NCU Theater Member Center***\nDo you have the membership? (y/n) ";
    char answer;
    if (!read_yes_no(answer)) return;
    if (answer == 'y') {
        string username, password;
        cout << "Enter Username: ";
        if (!read_text(username)) return;
        cout << "Enter Password: ";
        if (!read_text(password)) return;
        theater.logged_in = authenticate(theater, username, password);
        if (theater.logged_in == -1) cout << "The username and the password don't match.\n";
    } else {
        cout << "Would you like to sign up? (y/n) ";
        if (!read_yes_no(answer)) return;
        if (answer == 'n') { cout << "Okay! Have a nice day.\n"; return; }
        if (theater.members.size() >= 15) { cout << "The member center is full.\n"; return; }
        MemberData member;
        cout << "Enter Username: ";
        if (!read_text(member.username)) return;
        cout << "Enter Password: ";
        if (!read_text(member.password)) return;

        for (size_t i = 0; i < theater.members.size(); ++i)
            if (theater.members[i].username == member.username) {
                cout << "This username already exists.\n";
                return;
            }
        theater.members.push_back(member);
        cout << "Welcome! You are now a member of NCU theater.\nPlease log in again.\n";
    }
}
void reserve_seat(Theater& theater) {
    cout << "***Make a new reservation***\n";
    int first_available = -1;
    for (int i = 0; i < 15; ++i)
        if (!theater.reserved[i]) { first_available = i; break; }
    if (first_available == -1) { cout << "All seats have been reserved.\n"; return; }
    cout << "Do you need a specified seat? (y/n) ";
    char answer;
    if (!read_yes_no(answer)) return;
    int seat = first_available + 1;
    if (answer == 'y') {
        cout << "Enter the seat number: ";
        while (true) {
            if (!read_integer(seat, 1, 15)) return;
            if (!theater.reserved[seat - 1]) break;
            cout << "The seat has been reserved, please enter your selection again: ";
        }
    }
    theater.reserved[seat - 1] = true;
    cout << "The seat number " << seat << " is reserved for you...\n";
}
void cancel_seat(Theater& theater) {
    cout << "***Cancel an existing reservation***\nPlease enter the seat number which you want to cancel: ";
    int seat;
    if (!read_integer(seat, 1, 15)) return;
    if (theater.reserved[seat - 1]) {
        theater.reserved[seat - 1] = false;
        cout << "The seat number " << seat << " is available now...\n";
    } else cout << "The seat is not reserved\n";
}
void show_available(const Theater& theater) {
    cout << "***Show the all available seats***\n";
    for (int i = 0; i < 15; ++i) if (!theater.reserved[i]) cout << "seat " << i + 1 << '\n';
}
void show_seats(const Theater& theater) {
    cout << "***Show the status of all seats***\nSeat number       Status\n";
    for (int i = 0; i < 15; ++i)
        cout << "Seat " << left << setw(13) << i + 1 << (theater.reserved[i] ? "reserved" : "available") << '\n';
}
void show_member(const Theater& theater) {
    cout << "***NCU Theater Membership***\n";
    if (theater.members.empty()) cout << "No Member\n";
    else {
        cout << "No.  Username\n";
        for (size_t i = 0; i < theater.members.size(); ++i)
            cout << i + 1 << ".  " << theater.members[i].username << '\n';
    }
}
void load_member(Theater& theater) {
    cout << "***Load member information***\nPlease enter the member file name: ";
    string filename;
    if (!(cin >> filename)) return;
    ifstream infile(filename.c_str(), ios::in);
    if (!infile) { cout << "File could not be opened.\n"; return; }
    vector<MemberData> pending;
    string line;
    while (getline(infile, line)) {
        istringstream row(line);
        MemberData member;
        if (!(row >> member.username >> member.password)) continue;
        if (member.username == "Name" && member.password == "Password") continue;
        if (member.username.size() > 50 || member.password.size() > 50 ||
            theater.members.size() + pending.size() >= 15) {
            cout << "Invalid member data.\n";
            return;
        }
        pending.push_back(member);
    }
    theater.members.insert(theater.members.end(), pending.begin(), pending.end());
    cout << "The file " << filename << " has been loaded...\n";
}


int main() {
    Theater theater;
    while (true) {
        cout << "*** Welcome to NCU theater reservation system ***\n";
        if (theater.logged_in >= 0)
            cout << "***Welcome back " << theater.members[theater.logged_in].username << "***\n";
        cout << "Please type 1 to make a new reservation\n"
             << "Please type 2 to cancel an existing reservation\n"
             << "Please type 3 to show the all available seats\n"
             << "Please type 4 to show the status of all current seats\n";
        cout << (theater.logged_in >= 0 ? "Please type 5 to log-out\n" : "Please type 5 to member center\n");
        cout << "Please type 6 to show member\n";
        cout << "Please type 7 to load member information\n";
        cout << "Please type 8 to exit the system\n";

        cout << "Enter your selection Here: ";
        int selection;
        while (true) {
            if (!read_integer(selection, 1, 8)) return 0;

            break;
        }
        cout << '\n';
        if (selection == 8) {
            cout << "Thank you for using our system\nHave a nice day~~\n";
            return 0;
        }
        switch (selection) {
            case 1: reserve_seat(theater); break;
            case 2: cancel_seat(theater); break;
            case 3: show_available(theater); break;
            case 4: show_seats(theater); break;
            case 5:
                if (theater.logged_in >= 0) theater.logged_in = -1;
                else Member(theater);
                break;
            case 6: show_member(theater); break;
            case 7: load_member(theater); break;

        }
        if (!cin) return 0;
        cout << '\n';
    }
}
