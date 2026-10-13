// 2024 Lab 10.4 / P113036: find the Caesar key, then decrypt the complete message.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

char shift_letter(char letter, int amount) {
    if (letter >= 'a' && letter <= 'z') return static_cast<char>('a' + (letter - 'a' + amount + 26) % 26);
    if (letter >= 'A' && letter <= 'Z') return static_cast<char>('A' + (letter - 'A' + amount + 26) % 26);
    return letter;
}
int find_key(const vector<char>& message, const vector<char>& keyword) {
    if (keyword.empty() || keyword.size() > message.size()) return 0;
    for (int key = 1; key <= 26; ++key) {
        for (size_t start = 0; start + keyword.size() <= message.size(); ++start) {
            size_t i = 0;
            while (i < keyword.size() && message[start + i] == shift_letter(keyword[i], key)) ++i;
            if (i == keyword.size()) return key;
        }
    }
    return 0;
}
int main() {
    string line, word;
    if (!getline(cin, line) || !getline(cin, word)) return 0;
    if (!line.empty() && line.back() == '\r') line.pop_back();
    if (!word.empty() && word.back() == '\r') word.pop_back();
    vector<char> message(line.begin(), line.end()), keyword(word.begin(), word.end());
    const int key = find_key(message, keyword);
    if (key == 0) { cout << "not found\n"; return 0; }
    cout << key << '\n';
    for (size_t i = 0; i < message.size(); ++i) cout << shift_letter(message[i], -key);
    cout << '\n';
}
