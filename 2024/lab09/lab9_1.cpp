// 2024 P1130295: use an actual ten-element odd-number array.
#include <iostream>
#include <limits>
using namespace std;
int main() {
    int values[10];
    for (int i = 0; i < 10; ++i) values[i] = 1 + 2 * i;
    int index;
    while (true) {
        cout << "Please enter the index of the element (0 to 9): \n";
        if (!(cin >> index)) {
            if (cin.eof()) return 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (index >= 0 && index < 10) break;
        cout << "Invalid index. Please enter a value between 0 and 9.\n";
    }
    cout << values[index] << '\n';
}
