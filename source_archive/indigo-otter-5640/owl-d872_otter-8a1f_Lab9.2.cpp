#include <iostream>
using namespace std;

int main()
{
    int num[100];
    int N;
    int i, j, tmp;
    cout << "Enter a number: " << endl;
    cin >> N;
    for( i = 0 ; i < N ; i = i + 1 )
    {
        cin >> num[i];
    }
    for( i = 0 ; i < N ; i = i + 1 )
    {
        for( j = i + 1 ; j < N ; j = j + 1 )
        {
            if( num[i] > num[j] )
            {
                tmp = num[i];
                num[i] = num[j];
                num[j] = tmp;
            }
        }
    }
    cout << "After sorting: " << endl;
    for( i = 0 ; i < N ; i = i + 1 )
    {
        cout << num[i] << " ";
    }
    if(N%2 == 0)
    {
        cout << endl << "Median value of this series is: " << (num[N/2] + num[(N/2)-1]) / 2;
    }
    else
    {
        cout << endl << "Median value of this series is: " << num[N/2];
    }
    return 0;
}
