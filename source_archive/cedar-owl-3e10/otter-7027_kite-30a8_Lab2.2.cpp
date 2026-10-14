//lab2.2
#include <iostream>

using namespace std;

int main() {
    int num1, num2, operation1;
    cout << "Please input 2 different integers:" << endl;
    cin >> num1 >> num2;                            //input 2 number
    cout << "Please input the operation:" << endl;
    cin >> operation1;                             // choose operation

    if (operation1 == 1)
        cout << "Summation is " << num1 + num2 << endl; //Summation

    if (operation1 == 2)
        cout << "Multiplication is " << num1*num2 << endl;//Multiplication

    if (operation1 == 3)
        if (num1 > num2)                        //find larger
            cout << "Larger number is " << num1 << endl;
        else
            cout << "Larger number is " << num2 << endl;

    if (operation1 == 4)                             //find smaller
        if (num1 > num2)
            cout << "Smller number is " << num2 << endl;
        else
            cout << "Smaller number is " << num1 << endl;

    return 0;
}//end of main
