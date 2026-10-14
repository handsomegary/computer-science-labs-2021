#include <iostream>
using namespace std;

int main()
{
    //label:
        int i,j,n;
        cout << "Enter the size of the diamond: ";
        cin >> n;
        while (n < 3 || n > 4294967295 )
        {
            cout << "Enter again: ";
            cin >> n;
        }
        for(i = 1; i <= (n+1)/2; i++)
        {
            for(j = (n+1)/2+1-i; j >= 1; j--)
                cout << "*";
            for(j = 1; j <= 2*i - 1; j++)
                cout << " ";
            for(j = (n+1)/2+1-i; j >= 1; j--)
                cout << "*";
            cout << endl;
        }
        for(i = (n-1)/2; i >= 1; i--)
        {
            for(j = (n+1)/2+1-i; j >= 1; j--)
                cout << "*";
            for(j = 2*i-1; j >= 1; j--)
                cout << " ";
            for(j = (n+1)/2+1-i; j >= 1; j--)
                cout << "*";
            cout << endl;
        }
        //goto label;
}
