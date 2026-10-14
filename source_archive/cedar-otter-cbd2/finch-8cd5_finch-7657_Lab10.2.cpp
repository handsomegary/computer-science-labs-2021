#include <iostream>
#include<string>

using namespace std;

void find_mountain(int* const num, int* const Length, long long int array[], int index, long long int memory[], long long int* const start) {
    int cc = 0;
    for (int x = 2;x < index - 1;x++) {
        if (array[x - 1]<array[x] && array[x]>array[x + 1]) {
            *num += 1;
        }
    }
    for (int x = 1;x < index;x++) {
        if (array[x - 1] > array[x] && array[x] < array[x + 1]) {
            memory[cc + 1] = x;
            cc++;
        }
    }
    for (int x = 0;x <= (*num) + 1;x++) {
        if (memory[x + 1] - memory[x] > *Length) {
            *Length = memory[x + 1] - memory[x];
            *start = memory[x];
        }
    }
}

int main() {
    int num = 0;int length = 0;
    long long int start = 0;
    long long int array[50];
    long long int a, index = 0;
    long long int memory[500] = { 0 };
    while (cin >> a) {
        array[index++] = a;
        char ch = getchar();
        if (ch == '\n') {
            break;
        }
    }
    find_mountain(&num, &length, array, index, memory, &start);
    if (num != 0) {
        cout << num << endl;
    }
    for (int i = 0;i <= length;i++) {
        if (num == 0) {
            break;
        }
        cout << array[start + i] << " ";
    }
}