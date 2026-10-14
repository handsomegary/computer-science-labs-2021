#include <iostream>

using namespace std;

// Sort a sequence number
void sort_a_sequence_number(unsigned long long int x, long long int k[]) {
    int next = 18;
    int insert = k[next];//記住原先的數字
    int moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    next--;
    insert = k[next];//記住原先的數字
    moveitem = next;
    if (k[moveitem] >= k[moveitem - 1]) {
        k[moveitem] = k[moveitem - 1];
        k[moveitem - 1] = insert;
    }
    if (next < 0) {
        return sort_a_sequence_number(x - 1, k);
    }
    if (k[0] >= k[1] && k[1] >= k[2] && k[2] >= k[3] && k[3] >= k[4] && k[4] >= k[5] && k[5] >= k[6] && k[6] >= k[7] && k[7] >= k[8] && k[8] >= k[9] && k[9] >= k[10] && k[10] >= k[11] && k[11] >= k[12] && k[12] >= k[13] && k[13] >= k[14] && k[14] >= k[15] && k[15] >= k[16] && k[16] >= k[17] && k[17] >= k[18]) {
        return;
    }
}
// Divide a sequence number
long long int divide_a_sequence_number(long long int a, long long int b) {
    long long int c = a % 10;
    if (b > 0) {
        return divide_a_sequence_number(a / 10, b - 1);
    }
    else {
        return c;
    }
}


// Merge two sequence numbers
void combine(long long int num1, long long int num2) {

    if (num1 % 10 > num2 % 10) {
        cout << num1 % 10;
        combine(num1 / 10, num2);
    }
    else if (num1 % 10 < num2 % 10) {
        cout << num2 % 10;
        combine(num1, num2 / 10);
    }
    else if (num1 % 10 == num2 % 10 && num1 % 10 != 0 && num2 % 10 != 0) {
        cout << num1 % 10;
        cout << num2 % 10;
        combine(num1 / 10, num2 / 10);
    }
    else {
        return;
    }

}



int main() {
    long long int num1, num2;
    long long int d[19];
    long long int k[19];
    cout << "Please enter two sequence numbers:" << endl;
    cin >> num1 >> num2;
    d[0] = divide_a_sequence_number(num1, 0);
    d[1] = divide_a_sequence_number(num1, 1);
    d[2] = divide_a_sequence_number(num1, 2);
    d[3] = divide_a_sequence_number(num1, 3);
    d[4] = divide_a_sequence_number(num1, 4);
    d[5] = divide_a_sequence_number(num1, 5);
    d[6] = divide_a_sequence_number(num1, 6);
    d[7] = divide_a_sequence_number(num1, 7);
    d[8] = divide_a_sequence_number(num1, 8);
    d[9] = divide_a_sequence_number(num1, 9);
    d[10] = divide_a_sequence_number(num1, 10);
    d[11] = divide_a_sequence_number(num1, 11);
    d[12] = divide_a_sequence_number(num1, 12);
    d[13] = divide_a_sequence_number(num1, 13);
    d[14] = divide_a_sequence_number(num1, 14);
    d[15] = divide_a_sequence_number(num1, 15);
    d[16] = divide_a_sequence_number(num1, 16);
    d[17] = divide_a_sequence_number(num1, 17);
    d[18] = divide_a_sequence_number(num1, 18);
    k[0] = divide_a_sequence_number(num2, 0);
    k[1] = divide_a_sequence_number(num2, 1);
    k[2] = divide_a_sequence_number(num2, 2);
    k[3] = divide_a_sequence_number(num2, 3);
    k[4] = divide_a_sequence_number(num2, 4);
    k[5] = divide_a_sequence_number(num2, 5);
    k[6] = divide_a_sequence_number(num2, 6);
    k[7] = divide_a_sequence_number(num2, 7);
    k[8] = divide_a_sequence_number(num2, 8);
    k[9] = divide_a_sequence_number(num2, 9);
    k[10] = divide_a_sequence_number(num2, 10);
    k[11] = divide_a_sequence_number(num2, 11);
    k[12] = divide_a_sequence_number(num2, 12);
    k[13] = divide_a_sequence_number(num2, 13);
    k[14] = divide_a_sequence_number(num2, 14);
    k[15] = divide_a_sequence_number(num2, 15);
    k[16] = divide_a_sequence_number(num2, 16);
    k[17] = divide_a_sequence_number(num2, 17);
    k[18] = divide_a_sequence_number(num2, 18);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, d);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    sort_a_sequence_number(2147483647, k);
    long long int number1;
    long long int number2;
    number1 = 1 * d[0] + 10 * d[1] + 100 * d[2] + 1000 * d[3] + 10000 * d[4] + 100000 * d[5] + 1000000 * d[6] + 10000000 * d[7] + 100000000 * d[8] + 1000000000 * d[9] + 10000000000 * d[10];
    number2 = 1 * k[0] + 10 * k[1] + 100 * k[2] + 1000 * k[3] + 10000 * k[4] + 100000 * k[5] + 1000000 * k[6] + 10000000 * k[7] + 100000000 * k[8] + 1000000000 * k[9] + 10000000000 * k[10];
    cout << "Sorted result of the first sequence number: " << number1 << endl << "Sorted result of the second sequence number: " << number2 << endl << "Result: ";
    combine(number1, number2);
    return 0;
}
