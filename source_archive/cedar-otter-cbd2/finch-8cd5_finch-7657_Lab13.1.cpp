#include <iostream>
#include <string>

using namespace std;

void compare(string invoice, string array[], int index, int reward[]) {
    int counter = 0;
    int zzz = invoice.length() - 1;
    for (int y = 0;y < index + 1;y++) {
        string tmp = array[y];
        for (int x = zzz - 1;x >= 0;x--) {
            if (invoice[x] == tmp[x]) {
                counter++;
            }
            else {
                break;
            }
        }
        reward[y] = counter;
        counter = 0;
    }
}
void coutt(int reward[], string array[], int index) {
    int counter = 0;
    int uget = 0;
    for (int x = 0;x < index; x++) {
        if (reward[x] == 3) {
            cout << array[x] << " won 2 hundred dollars!" << endl;
            counter++;
            uget += 200;
        }
        if (reward[x] == 4) {
            cout << array[x] << " won 1 thousand dollars!" << endl;
            counter++;
            uget += 1000;
        }
        if (reward[x] == 5) {
            cout << array[x] << " won 4 thousand dollars!" << endl;
            counter++;
            uget += 4000;
        }
        if (reward[x] == 6) {
            cout << array[x] << " won 10 thousand dollars!" << endl;
            counter++;
            uget += 10000;
        }
        if (reward[x] == 7) {
            cout << array[x] << " won 40 thousand dollars!" << endl;
            counter++;
            uget += 40000;
        }
        if (reward[x] == 8) {
            cout << array[x] << " won 200 thousand dollars!" << endl;
            counter++;
            uget += 200000;
        }
    }
    if (counter != 0 && uget > 0) {
        cout << "You totally won " << uget << " dollars !!!";
    }
    if (counter == 0) {
        cout << "Won nothing. But, less is more.";
    }
}
int main() {
    string sentence;
    string invoice;
    string uhave;
    int index = 0;
    int reward[20];
    string array[20];
    getline(cin, sentence);
    invoice = sentence.substr(sentence.length() - 9, sentence.length() - 2);
    while (cin >> uhave) {
        array[index++] = uhave;
        char ch = getchar();
        if (ch == '\n') {
            break;
        }
    }
    compare(invoice, array, index, reward);
    cout << endl;
    coutt(reward, array, index);
}