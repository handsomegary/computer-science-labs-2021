// 2024 P113032: row-major neighbor bits; boundary LBP codes stay zero.
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
using namespace std;

int main() {
    long long rows, columns;
    cout << "Please enter the number of rows and columns: ";
    if (!(cin >> rows >> columns) || rows < 1 || columns < 1 ||
        rows > 2147483647LL || columns > 2147483647LL) { cout << "error\n"; return 1; }
    if (rows < 3 || columns < 3) {
        cout << "The size of the matrix must be at least 3x3 to compute LBP.\n";
        return 0;
    }
    if (static_cast<unsigned long long>(rows) > numeric_limits<size_t>::max() / static_cast<unsigned long long>(columns)) {
        cout << "error\n";
        return 1;
    }
    const size_t count = static_cast<size_t>(rows) * static_cast<size_t>(columns);
    unique_ptr<int[]> image, lbp;
    try { image.reset(new int[count]); lbp.reset(new int[count]()); }
    catch (const bad_alloc &) { cout << "error\n"; return 1; }
    while (true) {
        cout << "Please input the grayscale image matrix (each element should be an integer between 0 and 255):\n";
        bool valid = true;
        for (size_t i = 0; i < count; ++i) {
            if (!(cin >> image[i]) || image[i] < 0 || image[i] > 255) { valid = false; break; }
        }
        if (valid) break;
        if (cin.eof()) return 0;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input detected! Matrix values must be between 0 and 255.\n";
    }
    for (long long row = 1; row < rows - 1; ++row) {
        for (long long col = 1; col < columns - 1; ++col) {
            const size_t position = static_cast<size_t>(row * columns + col);
            unsigned bit = 0;
            for (int dr = -1; dr <= 1; ++dr)
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    const size_t neighbor = static_cast<size_t>((row + dr) * columns + col + dc);
                    if (image[neighbor] >= image[position]) lbp[position] |= 1 << bit;
                    ++bit;
                }
        }
    }
    cout << "LBP Matrix:\n";
    for (long long row = 0; row < rows; ++row) {
        for (long long col = 0; col < columns; ++col)
            cout << setw(5) << lbp[static_cast<size_t>(row * columns + col)];
        cout << '\n';
    }
}
