#include <iostream>
using namespace std;

int main()
{
    int n, i[100][100];
    while(true)
    {
        cout << "Please enter a number for the column of the Pascal triangle: " << endl;
        cin >> n;
        if(n == 0)
        {
            return 0;
        }
        else if (n == 1)
        {
            cout << 1 << endl;
        }
        else
        {
            i[1][1] = 1, i[2][1] = 1, i[2][2] = 1;
            cout << i[1][1] << endl;
            cout << i[2][1] << "  " << i[2][2] << endl;
            for(int j = 3; j <= n; j++)
            {
                i[j][1] = 1;
                cout << i[j][1] << "  ";
                for(int k = 2; k < j; k++)
                {
                    i[j][k] = i[j-1][k-1] + i[j-1][k];
                    cout << i[j][k] << "  ";
                }
                i[j][j] = 1;
            cout << i[j][j] << endl;
            }
        }
    }
}
