#include <iostream>

using namespace std;


int number_of_addition = 1, number_of_subtracttion = 1;

void add(int& x) {
    x += number_of_addition;
    ++number_of_addition;
    cout << endl << "The number now is " << x << endl;
    //please complete the function
}
void sub(int& x) {
    x -= number_of_subtracttion;
    ++number_of_subtracttion;
    cout << endl << "The number now is " << x << endl;
    //please complete the function
}
void factorization(long long int b) {
    long long int c = 1;
    cout << b << " = ";
    while (c < b) {
        if (b % c == 0) {
            cout << c << ",";
        }
        c++;
    }
    cout << c << endl << endl << "The number now is " << b << endl;;
    //please complete the function
}

int main() {
    int number = 0, choose;
    cout << "The number now is " << number << endl;
    while (true) {
        cout << "Choose a function:" << endl;
        cout << "1. Add    2. Sub    3. Factorization    4. Exit" << endl << endl;;
        cin >> choose;
        if (choose < 1 || choose>4) {
            cout << "Enter error!!" << endl << endl << "The number now is " << number << endl;
            continue;
        }
        if (choose == 1) {
            add(number);
        }
        if (choose == 2) {
            sub(number);
        }
        if (choose == 4) {
            break;
        }
        if (choose == 3) {
            if (number <= 0) {
                cout << "No factorization" << endl << endl << "The number now is " << number << endl;
            }
            else factorization(number);
        }
    }

    return 0;
}

