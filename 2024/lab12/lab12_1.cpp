// 2024 Lab 12.1 / P113041: store and access the five-element array via pointers.
#include <iostream>
using namespace std;
void reverse_output(const int *numbers) {
    for (int i = 4; i >= 0; --i) {
        if (i < 4) cout << ' ';
        cout << *(numbers + i);
    }
    cout << '\n';
}
int main() {
    int numbers[5];
    for (int i = 0; i < 5; ++i) if (!(cin >> *(numbers + i))) return 0;
    reverse_output(numbers);
}
