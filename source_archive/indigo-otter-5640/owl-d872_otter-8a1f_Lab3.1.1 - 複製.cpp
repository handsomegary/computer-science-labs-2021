#include <iostream>
using namespace std;

int binaryaddition(int a1, int a2);

int main()
{
    int binadd = binaryaddition(1,1);//(11011,100101001100010101);
    cout << "Binary Addition = " << binadd << endl;
    return 0;
}

int binaryaddition(int a1, int a2)
{
    int x = max(a1,a2);
    int y = min(a1,a2);
    int result = 0;
    int carry = 0;
    int place = 1;
    while(x >= 0)
    {
        a1 = x%10;
        a2 = y%10;
        result = ((a1+a2+carry)%2)*place + result;
        carry = (a1+a2+carry)/2;
    }
    return result;
}
