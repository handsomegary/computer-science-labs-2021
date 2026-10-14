#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

int main() {
    cout << "Enter a number:" << endl;
    int a;
    int insert;
    string kkk;
    cin >> a;
    vector <int> data(a);
    for (int i = 0;i <= a - 1; i++) {
        cin >> data[i];
    }
    for (int next = 1;next < a;next++) {
        insert = data[next];
        int moveItem = next;
        while ((moveItem > 0) && (data[moveItem - 1] > insert)) {
            data[moveItem] = data[moveItem - 1];
            moveItem--;
        }
        data[moveItem] = insert;
    }
    cout << "After sorting:" << endl;
    for (int k = 0;k < a - 1;k++) {
        cout << data[k] << " ";
    }
    cout << data[a - 1];
    cout << endl << "Median value of this series is: ";
    if (a % 2 == 1) {
        cout << data[a / 2];
    }
    if (a % 2 == 0) {
        cout << (data[a / 2] + data[a / 2 - 1]) / 2;
    }
}