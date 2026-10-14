#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct driver {
    int distance;
    int fine;
};

typedef driver Drive;

Drive which[100];

int main() {
    int driver;
    int length;
    int pay;
    int sum = 0;
    int route = 0;
    int index = 0;
    while (cin >> driver >> length >> pay) {
        for (int i = 0;i < 100;i++) {
            which[i].distance = 0;
            which[i].fine = 0;
        }
        if (driver == 0 && length == 0 && pay == 0) {
            break;
        }
        int morningarray[driver];
        int nightarray[driver];
        while (cin >> route) {
            morningarray[index++] = route;
            char ch = getchar();
            if (ch == '\n') {
                break;
            }
        }
        index = 0;
        while (cin >> route) {
            nightarray[index++] = route;
            char ch = getchar();
            if (ch == '\n') {
                break;
            }
        }
        sort(morningarray, morningarray + driver);
        sort(nightarray, nightarray + driver, greater<int>());
        for (int i = 0;i < driver;i++) {
            which[i].distance += morningarray[i];
            which[i].distance += nightarray[i];
        }
        for (int i = 0;i < driver;i++) {
            which[i].fine += (which[i].distance - length) * pay;
            if (which[i].distance - length < 0) {
                which[i].fine = 0;
            }
            sum += which[i].fine;
        }
        cout << sum << endl;
        sum = 0;
        index = 0;
    }
}