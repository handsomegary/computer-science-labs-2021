// 2024 Lab 12.4 / P113044: pointer-based iterative DFS in up/right/down/left order.
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

void pop(int& top, int *row, int *column, int *direction,
         const int *rowStack, const int *columnStack, const int *directionStack) {
    *row = *(rowStack + top);
    *column = *(columnStack + top);
    *direction = *(directionStack + top);
    --top;
}
void push(int& top, int row, int column, int direction,
          int *rowStack, int *columnStack, int *directionStack) {
    ++top;
    *(rowStack + top) = row;
    *(columnStack + top) = column;
    *(directionStack + top) = direction;
}
void path(const int *maze, int rows, int columns) {
    const int stride = columns + 2;
    const int start = stride + 1;
    const int exitIndex = rows * stride + columns;
    if (*(maze + start) != 0 || *(maze + exitIndex) != 0) {
        cout << "Can't reach the exit!\n";
        return;
    }
    const size_t capacity = static_cast<size_t>(rows) * columns + 1;
    vector<int> rowStorage(capacity), columnStorage(capacity), directionStorage(capacity);
    int *rowStack = rowStorage.data(), *columnStack = columnStorage.data(), *directionStack = directionStorage.data();
    vector<int> visited(static_cast<size_t>(rows + 2) * stride, 0);
    int *mark = visited.data();
    int offsets[8] = {-1,0, 0,1, 1,0, 0,-1};
    const int *move = offsets;
    int top = -1;
    push(top, 1, 1, 0, rowStack, columnStack, directionStack);
    *(mark + start) = 1;
    bool found = rows == 1 && columns == 1;
    while (top >= 0 && !found) {
        int row, column, direction;
        pop(top, &row, &column, &direction, rowStack, columnStack, directionStack);
        while (direction < 4 && !found) {
            const int nextRow = row + *(move + direction * 2);
            const int nextColumn = column + *(move + direction * 2 + 1);
            const int index = nextRow * stride + nextColumn;
            if (*(maze + index) == 0 && *(mark + index) == 0) {
                *(mark + index) = 1;
                push(top, row, column, direction + 1, rowStack, columnStack, directionStack);
                if (nextRow == rows && nextColumn == columns) {
                    push(top, nextRow, nextColumn, 0, rowStack, columnStack, directionStack);
                    found = true;
                } else {
                    row = nextRow;
                    column = nextColumn;
                    direction = 0;
                }
            } else ++direction;
        }
    }
    if (!found) cout << "Can't reach the exit!\n";
    else {
        for (int i = 0; i <= top; ++i) {
            if (i) cout << ' ';
            cout << '(' << *(rowStack + i) - 1 << ", " << *(columnStack + i) - 1 << ')';
        }
        cout << '\n';
    }
}
int main() {
    int rows, columns;
    if (!(cin >> rows >> columns) || rows < 1 || columns < 1) return 0;
    const long long size = (static_cast<long long>(rows) + 2) * (static_cast<long long>(columns) + 2);
    if (size > INT_MAX) return 0;
    vector<int> storage(static_cast<size_t>(size), 1);
    int *maze = storage.data();
    const int stride = columns + 2;
    for (int row = 1; row <= rows; ++row)
        for (int column = 1; column <= columns; ++column) {
            char cell;
            if (!(cin >> cell) || (cell != '0' && cell != '1')) return 0;
            *(maze + row * stride + column) = cell - '0';
        }
    path(maze, rows, columns);
}
