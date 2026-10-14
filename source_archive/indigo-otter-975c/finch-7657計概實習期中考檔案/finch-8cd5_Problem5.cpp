#include <iostream>
#include <iomanip>

using namespace std;

long long int decimaltooct(long long int a) { //recursion about decimal to binary
    if (a == 0) {
        return 0;
    }
    else {
        return(a % 8 + 10 * decimaltooct(a / 8));
    }
}
long long int decimaltobinary(long long int a) { //recursion about decimal to binary
    if (a == 0) {
        return 0;
    }
    else {
        return(a % 2 + 10 * decimaltobinary(a / 2));
    }
}

int main() {
    int x; //data 1
    int y; //data 2
    int z; //min
    int w; //max
    int k = 0;
    int g = 0;
    long long int memory = 9999999999;
    int memory2 = 0;

    while (1) {
        cin >> x;
        while (k < x) {
            cin >> z;

            if (z < memory) {
                memory = z;
            }
            k++;
        }
        cin >> y;
        while (g < y) {
            cin >> w;

            if (w > memory2) {
                memory2 = w;
            }
            g++;
        }
        if ((memory + memory2) % 2 == 0) {
            break;
        }
        else {
            memory = 9999999999;
            memory2 = 0;
            k = 0;
            g = 0;
            cout << "Input again!" << endl;
            continue;
        }

    }
    cout << "Input again!" << endl;
    cout << "Decimal " << (memory + memory2) / 2 << endl;
    cout << "Octet " << decimaltooct((memory + memory2) / 2) << endl;
    cout << "Binary " << decimaltobinary((memory + memory2) / 2) << endl;
    if ((memory + memory2) / 2 >= 63) {
        cout << "The country is rich";
    }
    else cout << "Come on";
}
