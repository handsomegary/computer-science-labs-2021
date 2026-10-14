#include <iostream>
#include <cmath>

using namespace std;

int degitcheck(int input) {
    int i = 0;
    int k = input / pow(10, i);

    while (k > 0) {
        i++;
        k = input / pow(10, i);
    }

    return i - 1;
}
void func1(int input) {
    int j = degitcheck(input), k = 0, l = 0;

    for (int i = j; i >= 1; i--) {
        l = input / pow(10, i);
        cout << l << "+";
        k = pow(10, i);
        input %= k;
    }

    cout <<input;
}
int func2(int input) {
    int temp = 0;

    while (input > 0) {
        temp += input % 10;
        input /= 10;
    }

    return temp;
}
int main() {
    int input = 0, level = 1;

    while (true) {
        cin >> input;

        if (input >= 0)
            break;
        else
            cout << "You should input a positive integer\n";
    }

    while (input >= 10) {

        for (int i = 0; i < level; i++)
            cout << "f" << "(";

        cout << "n";

        for (int i = 0; i < level; i++)
            cout << ")";

        cout << "=";
        func1(input);
        cout << "=" << func2(input);
        cout << endl;
        input = func2(input);

        level++;

    }

    cout << "The summing digit is:" << input;
    return 0;
}
