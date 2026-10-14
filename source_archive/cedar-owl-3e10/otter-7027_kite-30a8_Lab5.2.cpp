#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int row,b;
    cout << "Enter number of rows: ";
    cin>>row;
    int a=row-1;
    for(int i=1;i<=row;i++)
    {
        for(int k=1;k<=4*a+1;k++)
            cout<<" ";
        if(i>1)
            b=(2+(i-1-1)*2)*(i-1)/2;
        else
            b=0;

        for(int j=b+1;j<=i*i;j++)
        {
            cout<<setw(3)<<j<<" ";
        }
        a--;
        cout<<endl;

    }

    return 0;
}
