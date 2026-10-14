#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int x;
    int y;
    int memory = 0;
    int array[4][9] = { {},{0,40,40,55,55,60,60,55,55},{0,55,55,60,70,85,95,100,110},{0,85,100,100,100} };
    cout << "-----Menu-----" << endl;
    while (1) {
        cin >> x;
        if (x == 0) {
            cout << "Total Cost: ";
            cout << memory;
            break;
        }
        cin >> y;
        if (y == 0) {
            cout << "Total Cost: ";
            cout << memory;
            break;
        }
        memory += array[x][y];
    }
}