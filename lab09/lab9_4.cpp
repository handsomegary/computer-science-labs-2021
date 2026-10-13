#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

void printspiralgraph(int size) {
    int spiralgraph[31][31] = {};
    int top = 0, bottom = size - 1, left = 0, right = size - 1, next = 1;
    while (top <= bottom && left <= right) {
        for (int col = left; col <= right; ++col) spiralgraph[top][col] = next++;
        ++top;
        for (int row = top; row <= bottom; ++row) spiralgraph[row][right] = next++;
        --right;
        if (top <= bottom) {
            for (int col = right; col >= left; --col) spiralgraph[bottom][col] = next++;
            --bottom;
        }
        if (left <= right) {
            for (int row = bottom; row >= top; --row) spiralgraph[row][left] = next++;
            ++left;
        }
    }
    const int digits = size * size < 10 ? 1 : size * size < 100 ? 2 : 3;
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col)
            cout << setfill('0') << setw(digits) << spiralgraph[row][col] << ' ';
        cout << '\n';
    }
    cout << setfill(' ');
}
int main() {
    int size;
    while (true) {
        cout << "Input dimension: ";
        if (!(cin >> size)) {
            if (cin.eof()) return 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            continue;
        }
        cout << '\n';
        if (size == -1) return 0;
        if (size < 3 || size > 31) { cout << "Invalid input\n"; continue; }
        printspiralgraph(size);
        cout << '\n';
    }
}
