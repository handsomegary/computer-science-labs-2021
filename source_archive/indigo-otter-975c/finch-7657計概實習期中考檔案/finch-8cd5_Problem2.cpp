#include <iostream>


using namespace std;

int divide() {

}

int main() {
    long long int x;
    int l;
    cin >> x;
    while (x < 0) {
        cout << "You should input a positive integer" << endl;
        cin >> x;
    }
    int q, w, e, r, t, y, u, i, o, p;
    p = x % 10;
    o = (x / 10) % 10;
    i = (x / 100) % 10;
    u = (x / 1000) % 10;
    y = (x / 10000) % 10;
    t = (x / 100000) % 10;
    r = (x / 1000000) % 10;
    e = (x / 10000000) % 10;
    w = (x / 100000000) % 10;
    q = (x / 1000000000) % 10;
    l = q + w + e + r + t + y + u + i + o + p;
    cout << "f(n)=";
    if (q != 0) cout << q << "+";
    if (w != 0) cout << w << "+";
    if (e != 0) cout << e << "+";
    if (r != 0)cout << r << "+";
    if (t != 0)cout << t << "+";
    if (y != 0)cout << y << "+";
    if (u != 0)cout << u << "+";
    if (i != 0)cout << i << "+";
    if (o != 0) cout << o << "+";
    cout << p;
    cout << "=" << l << endl;
    while (1) {

        if (l / 10 == 0) {
            cout << "The summing digit is:" << l;
            break;
        }
        q = l / 10;
        w = l % 10;
        x = q + w;
        cout << "f(f(n))=" << q << "+" << w << "=" << x << endl;
        if (x / 10 == 0) {
            cout << "The summing digit is:" << x;
            break;
        }
        q = x / 10;
        w = x % 10;
        x = q + w;
        cout << "f(f(f(n)))=" << q << "+" << w << "=" << x << endl;
        cout << "The summing digit is:" << x;
        break;
    }
    return 0;
}
