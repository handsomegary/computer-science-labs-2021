#include <iostream>
#include <string>

using namespace std;

void swap(int* const elementptr, int* const element2ptr) {
    int hold = *elementptr;
    *elementptr = *element2ptr;
    *element2ptr = hold;
}
void sorting(int* array, const int size, bool(*ascending)(int, int), bool(*descending)(int, int)) {
    int small;
    int ascending11[20], descending11[20];

    for (int i = 0;i < size - 1;i++) {
        small = i;
        for (int index = i + 1; index < size;index++)
            if (!(*ascending)(array[small], array[index]))
                small = index;
        swap(&array[small], &array[i]);
    }
    for (int i = 0;i < size;i++) {
        ascending11[i] = array[i];
    }
    for (int i = 0;i < size - 1;i++) {
        small = i;
        for (int index = i + 1; index < size;index++)
            if (!(*descending)(array[small], array[index]))
                small = index;
        swap(&array[small], &array[i]);
    }
    for (int i = 0;i < size;i++) {
        descending11[i] = array[i];
    }

    for (int k = 0;k < size / 2;k++) {
        cout << descending11[k] << " " << ascending11[k] << " ";
    }
    if (size % 2 != 0) {
        cout << ascending11[size / 2];
    }
}
bool ascending(int a, int b) {
    return a < b;
}
bool descending(int a, int b) {
    return a > b;
}
int main() {
    int array[20];
    int a, size = 0;
    while (cin >> a) {
        array[size++] = a;
        char ch = getchar();
        if (ch == '\n') {
            break;
        }
    }
    sorting(array, size, ascending, descending);
}