#include <iostream>
#include <string>
using namespace std;

void capitalizeWords(string &sentence) {
    bool beginning = true;
    for (size_t i = 0; i < sentence.size(); ++i) {
        if (sentence[i] == ' ') beginning = true;
        else {
            if (beginning && sentence[i] >= 'a' && sentence[i] <= 'z')
                sentence[i] = static_cast<char>(sentence[i] - ('a' - 'A'));
            beginning = false;
        }
    }
}

int main() {
    string sentence1, sentence2;
    cout << "Input Line1: ";
    if (!getline(cin, sentence1)) return 0;
    cout << "Input Line2: ";
    if (!getline(cin, sentence2)) return 0;
    if (sentence1.size() > 50 || sentence2.size() > 50) {
        cout << "Input line exceeds 50 characters\n";
        return 1;
    }
    capitalizeWords(sentence1);
    capitalizeWords(sentence2);
    cout << "Output Line: " << sentence1 << ' ' << sentence2 << '\n';
}
