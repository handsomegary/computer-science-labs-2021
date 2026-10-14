#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    long long int x;
    long long j = 1;
    cout << "Enter number of rows: ";
    cin >> x;

    for (int q = 1; q <= x; q++)
    {
        for (int y = 0; y < x - q; y++)
        {
            cout << "    ";
        }

        for (; j <= q * q; j++)
        {
            cout << setw(4) << j;

            while (j == q * q)
            {
                cout << endl;
                break;
            }
        }
    }

    system("pause");
}