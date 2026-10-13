// 2021 final E: the prescribed encrypt class, with spaces preserved.
#include <iostream>
#include <limits>
#include <string>
using namespace std;

class encrypt {
public:
    explicit encrypt(string text) : information(text) {}
    void encryption() {
        for (size_t i = 0; i < information.size(); ++i) {
            if (information[i] == ' ') continue;
            const int value = static_cast<unsigned char>(information[i]);
            const int changed = i % 2 == 0 ? value + key * key : value - key;
            information[i] = static_cast<char>(static_cast<unsigned char>(changed));
        }
    }
    void decryption() {
        for (size_t i = 0; i < information.size(); ++i) {
            if (information[i] == ' ') continue;
            const int value = static_cast<unsigned char>(information[i]);
            const int changed = i % 2 == 0 ? value - key * key : value + key;
            information[i] = static_cast<char>(static_cast<unsigned char>(changed));
        }
    }
    void print_information() { cout << information << '\n'; }
private:
    string information;
    int key = 3;
};
int main() {
    cout << "Welcome to encryption system!\nEnter 1 to encrypt\nEnter 2 to decrypt\n";
    int mode;
    if (!(cin >> mode) || (mode != 1 && mode != 2)) { cout << "error\n"; return 1; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nInput information: ";
    string information;
    if (!getline(cin, information)) return 1;
    if (!information.empty() && information.back() == '\r') information.pop_back();
    encrypt message(information);
    if (mode == 1) { message.encryption(); cout << "Encrypted information: "; }
    else { message.decryption(); cout << "Decrypted information: "; }
    message.print_information();
}
