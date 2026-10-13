// 2024 Lab 12.3 / P113043: independent hotel booking system.
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Room {
    string number, hotel, type, distance;
    int people, price;
};
struct Reservation { string name, date; int room; };
const Room rooms[8] = {
    {"1-1", "Cloud Hotel", "Double", "0.6km", 2, 1650},
    {"1-2", "Cloud Hotel", "Quad", "0.6km", 4, 3200},
    {"2-1", "Garden Hotel", "Single", "1km", 1, 760},
    {"2-2", "Garden Hotel", "Double", "1km", 2, 1380},
    {"2-3", "Garden Hotel", "Twin", "1km", 2, 1420},
    {"3-1", "City Big Hotel", "Double", "1.5km", 2, 2540},
    {"3-2", "City Big Hotel", "Triple", "1.5km", 3, 3670},
    {"3-3", "City Big Hotel", "Quad", "1.5km", 4, 4300}
};
const bool limited_rooms = true;

int Rooms(const string& number) {
    for (int i = 0; i < 8; ++i) if (rooms[i].number == number) return i;
    return -1;
}
bool is_available(const vector<vector<string> >& not_available, const string& date, const string& number) {
    if (!limited_rooms) return true;
    for (size_t i = 0; i < not_available.size(); ++i)
        if (not_available[i][0] == date && not_available[i][1] == number) return false;
    return true;
}
bool read_date(string& date) {
    string token;
    const int days[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    while (cin >> token) {
        istringstream parser(token);
        int month, day;
        char slash, extra;
        if (parser >> month >> slash >> day && !(parser >> extra) && slash == '/' &&
            month >= 1 && month <= 12 && day >= 1 && day <= days[month - 1]) {
            date = to_string(month) + '/' + to_string(day);
            return true;
        }
        cout << "Wrong date, please enter again!\nEnter date: ";
    }
    return false;
}
bool read_people(int& people) {
    string token;
    while (cin >> token) {
        istringstream parser(token);
        char extra;
        if (parser >> people && !(parser >> extra) && people >= 1 && people <= 4) return true;
        cout << "Invalid number of people, please enter again!\nHow many people? ";
    }
    return false;
}
void Search_System(const vector<vector<string> >& not_available) {
    string date;
    int people;
    cout << "Enter date: ";
    if (!read_date(date)) return;
    cout << "How many people? ";
    if (!read_people(people)) return;
    cout << '\n';
    string currentHotel;
    bool any = false;
    for (int i = 0; i < 8; ++i) {
        if (rooms[i].people != people || !is_available(not_available, date, rooms[i].number)) continue;
        if (currentHotel != rooms[i].hotel) {
            if (any) cout << '\n';
            currentHotel = rooms[i].hotel;
            cout << "*** " << left << setw(20) << currentHotel
                 << "Distance: " << rooms[i].distance << " ***\n"
                 << left << setw(4) << "No." << setw(35) << "Room" << "Price\n";
        }
        cout << left << setw(4) << rooms[i].number << setw(35) << rooms[i].type
             << "NTD " << right << setw(4) << rooms[i].price << '\n';
        any = true;
    }
    if (!any) cout << "No available rooms.\n";
    cout << '\n';
}
void Reserve_System(vector<Reservation>& reservations, vector<vector<string> >& not_available) {
    Reservation booking;
    cout << "Enter your name: ";
    if (!getline(cin >> ws, booking.name)) return;
    cout << "Enter date: ";
    if (!read_date(booking.date)) return;
    string number;
    while (true) {
        cout << "Enter room number to reserve: ";
        if (!(cin >> number)) return;
        booking.room = Rooms(number);
        if (booking.room == -1) { cout << "Wrong number, please enter again!\n"; continue; }
        if (!is_available(not_available, booking.date, number)) {
            cout << "The selected room is not available, please enter again!\n";
            continue;
        }
        if (limited_rooms) {
            vector<string> entry;
            entry.push_back(booking.date);
            entry.push_back(number);
            not_available.push_back(entry);
        }
        reservations.push_back(booking);
        cout << "Reserved successfully!\n\n";
        return;
    }
}
void Payment(const vector<Reservation>& reservations) {
    string name;
    cout << "Enter your name: ";
    if (!getline(cin >> ws, name)) return;
    bool found = false;
    long long total = 0;
    for (size_t i = 0; i < reservations.size(); ++i) {
        const Reservation& booking = reservations[i];
        if (booking.name != name) continue;
        if (!found) cout << "\n*** This is " << name << "'s order ***\n";
        found = true;
        const Room& room = rooms[booking.room];
        cout << "Date: " << booking.date << '\n'
             << left << setw(35) << "Hotel" << "Price\n"
             << "---------------------------------------------\n"
             << left << setw(35) << room.hotel + ' ' + room.type + " Room"
             << "NTD " << right << setw(4) << room.price << "\n\n";
        total += room.price;
    }
    if (!found) cout << "You have not reserved any rooms.\n\n";
    else cout << "---------------------------------------------\n"
              << left << setw(35) << "Total" << "NTD " << right << setw(4) << total << "\n\n";
}
int main() {
    vector<Reservation> reservations;
    // Lab 12.3's prescribed date/room table; disabled for the unlimited Lab 11.3.
    vector<vector<string> > not_available;
    string command;
    while (true) {
        cout << "1. Search System\n2. Reserve System\n3. Payment\nexit(). Quit\n>>> ";
        if (!(cin >> command)) return 0;
        if (command == "exit()" || command == "exit" || command == "0") return 0;
        cout << '\n';
        if (command == "1") Search_System(not_available);
        else if (command == "2") Reserve_System(reservations, not_available);
        else if (command == "3") Payment(reservations);
        else cout << "Unknown command\n\n";
        if (!cin) return 0;
    }
}
