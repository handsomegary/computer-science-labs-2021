#include <iostream>

using namespace std;

int main(void)
{
    int num1, num2, option, answer;
    cout << "Please input 2 different integers: " << endl;
    cin >> num1;
    cin >> num2;
    cout << "Please input the operation: " << endl;
    cin >> option ;
    if (option == 1)
        cout << "Summation is " << num1 + num2 ;
    if (option == 2)
        cout << "Multiplication is " << num1*num2 ;
    if (option == 3)
        if (num1 > num2)
            cout << "Larger number is " << num1 << endl;
        else
            cout << "Larger number is " << num2 << endl;
    if (option == 4)
        if (num1 < num2)
            cout << "Smaller number is " << num1 << endl;
        else
            cout << "Smaller number is " << num2 << endl;
    return 0;
}
