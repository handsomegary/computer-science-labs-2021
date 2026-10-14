#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int z;
    int y;
    cin >> z;
    cin >> y;
    int x = z;
    while (1) {
        while (x < y) {
            int q, w, e, r, t, l, u, i, o, p;
            int qq = log10(x) + 1;
            p = x % 10;
            o = (x / 10) % 10;
            i = (x / 100) % 10;
            u = (x / 1000) % 10;
            l = (x / 10000) % 10;
            t = (x / 100000) % 10;
            r = (x / 1000000) % 10;
            e = (x / 10000000) % 10;
            w = (x / 100000000) % 10;
            q = (x / 1000000000) % 10;
            if ((pow(p, qq) + pow(o, qq) + pow(i, qq) + pow(u, qq) + pow(l, qq) + pow(t, qq) + pow(r, qq) + pow(e, qq) + pow(w, qq) + pow(q, qq)) == x) {
                cout << x;
                x++;
                break;
            }
            x++;
        }
        while (x < y) {
            int q, w, e, r, t, l, u, i, o, p;
            int qq = log10(x) + 1;
            p = x % 10;
            o = (x / 10) % 10;
            i = (x / 100) % 10;
            u = (x / 1000) % 10;
            l = (x / 10000) % 10;
            t = (x / 100000) % 10;
            r = (x / 1000000) % 10;
            e = (x / 10000000) % 10;
            w = (x / 100000000) % 10;
            q = (x / 1000000000) % 10;
            if ((pow(p, qq) + pow(o, qq) + pow(i, qq) + pow(u, qq) + pow(l, qq) + pow(t, qq) + pow(r, qq) + pow(e, qq) + pow(w, qq) + pow(q, qq)) == x) {
                cout << " & " << x;
            }
            x++;
        }
        if (y - z <= 500) {
            cout << "none";
            break;
        }
        break;

    }
}
