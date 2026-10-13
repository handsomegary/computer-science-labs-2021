// 2024 Lab 11.4 / P113040: Apple and Banana, including leading-zero secrets.
#include <iostream>
#include <string>
using namespace std;

bool valid_digits(const string& number, int length, bool unique) {
    if (number.size() != static_cast<size_t>(length)) return false;
    bool seen[10] = {};
    for (int i = 0; i < length; ++i) {
        if (number[i] < '0' || number[i] > '9') return false;
        const int digit = number[i] - '0';
        if (unique && seen[digit]) return false;
        seen[digit] = true;
    }
    return true;
}
void score(const char *secret, const char *guess, int length, int *apple, int *banana) {
    int secret_count[10] = {}, guess_count[10] = {};
    *apple = *banana = 0;
    for (int i = 0; i < length; ++i) {
        if (secret[i] == guess[i]) ++*apple;
        else { ++secret_count[secret[i] - '0']; ++guess_count[guess[i] - '0']; }
    }
    for (int digit = 0; digit < 10; ++digit)
        *banana += secret_count[digit] < guess_count[digit] ? secret_count[digit] : guess_count[digit];
}
int main() {
    int length;
    if (!(cin >> length)) return 0;
    if (length < 3 || length > 8) { cout << "Invalid length.\n"; return 0; }
    const int limits[6] = {4,7,11,16,22,29};
    string input;
    if (!(cin >> input)) return 0;
    if (!valid_digits(input, length, true)) { cout << "Invalid secret number.\n"; return 0; }
    char secret[8], guess[8];
    for (int i = 0; i < length; ++i) secret[i] = input[i];
    for (int attempt = 0; attempt < limits[length - 3];) {
        if (!(cin >> input)) return 0;
        if (!valid_digits(input, length, false)) { cout << "Invalid guess, please enter again.\n"; continue; }
        for (int i = 0; i < length; ++i) guess[i] = input[i];
        int apple, banana;
        score(secret, guess, length, &apple, &banana);
        ++attempt;
        cout << apple << 'A' << banana << "B\n";
        if (apple == length) { cout << "You win!\n"; return 0; }
    }
    cout << "You lose!\n";
}
