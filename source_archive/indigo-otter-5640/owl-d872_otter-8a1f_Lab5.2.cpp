#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int rows = 0;
    cout << "Enter number of rows: ";
    cin >> rows;
    for(int i = 1;i <= rows;i++)
    {
        int p = (i-1)*(i-1) + 1;
        for(int j = 1;j <= (rows - i);j++)
        {
            cout << setw(4) << " ";
        }
        for(int k = 1;k <= (2*i-1);k++)
        {
            cout << setw(4) << p;
            p++;
        }
        for(int j = 1;j <= (rows - i);j++)
        {
            cout << setw(4) << " ";
        }
        cout << endl;
    }
}
