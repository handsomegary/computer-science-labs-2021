// Completed from LAB7_2_smaple.cpp: recursion only, no loop statements.
#include <iostream>
using namespace std;

long long insertDigit(long long sorted, long long digit) {
    if (sorted == 0 || sorted % 10 <= digit) return sorted * 10 + digit;
    return insertDigit(sorted / 10, digit) * 10 + sorted % 10;
}
long long sort_a_sequence_number(long long number);
long long divide_a_sequence_number(long long number) {
    return sort_a_sequence_number(number / 10);
}
long long sort_a_sequence_number(long long number) {
    if (number < 10) return number;
    return insertDigit(divide_a_sequence_number(number), number % 10);
}
void combine(long long num1, long long num2) {
    if (num1 == 0 && num2 == 0) return;
    if (num1 % 10 > num2 % 10) {
        cout << num1 % 10;
        combine(num1 / 10, num2);
    } else if (num1 % 10 < num2 % 10) {
        cout << num2 % 10;
        combine(num1, num2 / 10);
    } else {
        cout << num1 % 10 << num2 % 10;
        combine(num1 / 10, num2 / 10);
    }
}
int main() {
    long long num1, num2;
    cout << "Please enter two sequence numbers:\n";
    if (!(cin >> num1 >> num2)) return 0;
    num1 = sort_a_sequence_number(num1);
    num2 = sort_a_sequence_number(num2);
    cout << "Sorted result of the first sequence number: " << num1 << '\n';
    cout << "Sorted result of the second sequence number: " << num2 << '\n';
    cout << "Result: ";
    combine(num1, num2);
    cout << '\n';
}
