// 2021 final A: an expanding clockwise spiral, clipped to the rectangle.
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool readInteger(int& number) {
    string token;
    while (cin >> token) {
        if (token == "Width,Length" || token == "x,y") continue;
        istringstream input(token);
        return static_cast<bool>(input >> number) && input.peek() == char_traits<char>::eof();
    }
    return false;
}
int main() {
    int rows, columns, row, column;
    if (!readInteger(rows) || !readInteger(columns) || !readInteger(row) || !readInteger(column) ||
        rows < 3 || rows > 31 || columns < 3 || columns > 31 || row < 0 || row >= rows ||
        column < 0 || column >= columns) { cout << "error\n"; return 1; }
    int graph[31][31] = {};
    const int dr[4] = {0, 1, 0, -1}, dc[4] = {1, 0, -1, 0};
    const int total = rows * columns;
    int value = 1, direction = 0, distance = 1;
    graph[row][column] = value++;
    while (value <= total) {
        // Segment lengths 1,1,2,2,3,3,...; off-grid positions consume steps,
        // but do not consume sequence numbers or change the spiral geometry.
        for (int segment = 0; segment < 2 && value <= total; ++segment) {
            for (int step = 0; step < distance && value <= total; ++step) {
                row += dr[direction];
                column += dc[direction];
                if (row >= 0 && row < rows && column >= 0 && column < columns && graph[row][column] == 0)
                    graph[row][column] = value++;
            }
            direction = (direction + 1) % 4;
        }
        ++distance;
    }
    const int digits = total < 10 ? 1 : total < 100 ? 2 : 3;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (c) cout << ' ';
            cout << setfill('0') << setw(digits) << graph[r][c];
        }
        cout << '\n';
    }
}
