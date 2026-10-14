#include <iostream>

using namespace std;

int main() {
    int x;
    int y;
    int z; //chicks
    int g; //rabbits
    while (true) {
        cin >> x >> y;
        if ((y - 2 * x) % 2 != 0 || (4 * x - y) % 2 != 0 || y - 2 * x < 0 || 4 * x - y < 0) {
            cout << "no" << endl;
            continue;
        }
        g = (y - 2 * x) / 2;
        z = (4 * x - y) / 2;
        if (x == 0 && y == 0) {
            cout << "Bye";
            break;
        }
        cout << "Chick " << z << " Rabbit " << g << endl;
    }
    return 0;
}
