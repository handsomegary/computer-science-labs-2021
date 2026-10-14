#include <iostream>
using namespace std;

int main() {
    int n;
    unsigned long long factorial;
    factorial = 1;
    cout << "Please enter a nonnegative integer: ";
    cin >> n;
    if (n == 0)
        {cout << "The corresponding factorial is " << factorial;}
    else if ( n > 0 )
        {for(int i = 1; i <= n; i = i + 1)
        {factorial =factorial*i;}
        cout << "The corresponding factorial is " << factorial;}
    return 0;
}
