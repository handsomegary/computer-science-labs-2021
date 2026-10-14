#include <iostream>
#include<string>
using namespace std;

void swap(long long int* const a, long long int* const b) {
    long long int tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse(int a, int b, long long int array[]) {
    while (a < b) {
        b--;
        swap(&array[a], &array[b]);
        a++;
    }
}

int main() {
    long long int array[100];
    long long int a, index = 0;
    while (cin >> a) {
        array[index++] = a;
        char ch = getchar();
        if (ch == '\n') {
            break;
        }
    }
    reverse(0, index, array);
    for (int i = 0;i < index;i++) {
        cout << array[i] << " ";
    }
}