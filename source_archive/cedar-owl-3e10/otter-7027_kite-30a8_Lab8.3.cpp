#include <iostream>

using namespace std;
void show(int);

int main()
{
    int number;
    do
    {
         cout << "Please enter a number for the column of the Pascal triangle:" << endl;
         cin>>number;
         if(number==0)   break;
         show(number);


    }while(number!=0);

    return 0;
}
void show(int num)
{
    int a[num][num];
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
        a[i][j]=0;

    for(int i=0;i<num;i++)
    {
        a[i][0]=1;
    }
    for(int i=1;i<num;i++)
        for(int j=1;j<num;j++)
        {
            a[i][j]=a[i-1][j-1]+a[i-1][j];
        }

    for(int i=0;i<num;i++)
    {
        for(int j=0;j<num;j++)
        {
            if(a[i][j]!=0)
            cout<<a[i][j]<<"  ";
        }
        cout<<endl;
    }

}
