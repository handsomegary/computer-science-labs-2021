#include <iostream>
#include <string>
using namespace std;


class encrypt {
public:
    void stringset(string a) {
        information = a;
    }
    void encryption() {
        for (int i = 0; i < information.length();i++) {
            if (information[i] == '\ ') {
                continue;
            }
            if (i % 2 == 0) {
                information[i] += 9;
            }
            else {
                information[i] -= 3;
            }
        }
    }
    void decryption() {
        for (int i = 0; i < information.length();i++) {
            if (information[i] == '\ ') {
                continue;
            }
            if (i % 2 == 0) {
                information[i] -= 9;
            }
            else {
                information[i] += 3;
            }
        }
    }
    void print_information() {
        cout << information;
    }
private:
    string information;
    int key = 3;
};


int main() {
    encrypt aaa;
    string iii;
    string kkk = "\0";
    int input;
    cout << "Welcome to encryption system!\nEnter 1 to encrypt\nEnter 2 to decrypt" << endl;
    cin >> input;
    cout << endl << "Input information: ";
    while (cin >> iii) {
        kkk += iii;
        kkk += '\ ';
        char ch = getchar();
        if (ch == '\n')
            break;
    }
    aaa.stringset(kkk);
    if (input == 1) {
        aaa.encryption();
        cout << "Encrypted information: ";
        aaa.print_information();
    }
    if (input == 2) {
        aaa.decryption();
        cout << "Decrypted information: ";
        aaa.print_information();
    }
    return 0;
}
