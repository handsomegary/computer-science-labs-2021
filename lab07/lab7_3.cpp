#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// The only global variables permitted by the provided template.
int number_of_addition = 1;
int number_of_subtracttion = 1;

void add(int &number, int &number_of_addition) {
    if (number_of_addition == numeric_limits<int>::max() ||
        number > numeric_limits<int>::max() - number_of_addition) {
        cout << "Enter error!!\n";
        return;
    }
    number += number_of_addition;
    ++number_of_addition;
}
void sub(int &number, int &number_of_substracttion) {
    if (number_of_substracttion == numeric_limits<int>::max() ||
        number < numeric_limits<int>::min() + number_of_substracttion) {
        cout << "Enter error!!\n";
        return;
    }
    number -= number_of_substracttion;
    ++number_of_substracttion;
}
void factorization(int number) {
    if (number <= 0) {
        cout << "No factorization\n";
        return;
    }
    vector<int> small, large;
    for (int i = 1; i <= number / i; ++i) {
        if (number % i == 0) {
            small.push_back(i);
            if (i != number / i) large.push_back(number / i);
        }
    }
    cout << number << " = ";
    for (size_t i = 0; i < small.size(); ++i) {
        if (i) cout << ',';
        cout << small[i];
    }
    for (size_t i = large.size(); i > 0; --i) cout << ',' << large[i - 1];
    cout << '\n';
}

bool readChoice(int &choice) {
    string token;
    if (!(cin >> token)) return false;
    istringstream input(token);
    if (!(input >> choice) || input.peek() != char_traits<char>::eof()) choice = 0;
    return true;
}

int main() {
    int number = 0, choose;
    while (true) {
        cout << "The number now is " << number << '\n'
             << "Choose a function:\n"
             << "1. Add    2. Sub    3. Factorization    4. Exit\n\n";
        if (!readChoice(choose)) return 0;
        if (choose == 1) add(number, number_of_addition);
        else if (choose == 2) sub(number, number_of_subtracttion);
        else if (choose == 3) factorization(number);
        else if (choose == 4) return 0;
        else cout << "Enter error!!\n";
    }
}
