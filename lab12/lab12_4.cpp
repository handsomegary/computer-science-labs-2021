// Based on the original lab; backtrack safely in all four directions.
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

bool search(char board[9][9], bool used[9][9], const string& word,
            size_t index, int row, int column) {
    if (row < 0 || row >= 9 || column < 0 || column >= 9 || used[row][column] ||
        board[row][column] != word[index]) return false;
    if (index + 1 == word.size()) return true;
    used[row][column] = true;
    const bool found = search(board, used, word, index + 1, row - 1, column) ||
                       search(board, used, word, index + 1, row + 1, column) ||
                       search(board, used, word, index + 1, row, column - 1) ||
                       search(board, used, word, index + 1, row, column + 1);
    used[row][column] = false;
    return found;
}
int main() {
    ifstream infile;
    infile.open("4_1.txt", ios::in);
    if (!infile) { cout << "File could not be opened.\n"; return 0; }
    char board[9][9];
    for (int row = 0; row < 9; ++row)
        for (int column = 0; column < 9; ++column)
            if (!(infile >> board[row][column])) { cout << "File contains an invalid board.\n"; return 0; }
    string word;
    while (cin >> word && word != "-1") {
        bool found = false, used[9][9] = {};
        if (word.size() <= 81)
            for (int row = 0; row < 9 && !found; ++row)
                for (int column = 0; column < 9 && !found; ++column)
                    found = search(board, used, word, 0, row, column);
        cout << (found ? "True" : "False") << '\n';
    }
}
