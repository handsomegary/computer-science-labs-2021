#include <iostream>
#include <iomanip>
using namespace std;





int main()
{
int ent;
cout <<"Enter number of rows: ";
cin>>ent;
for(int level=1;level<=ent;level++)
{   int k=level*level-2*level+2;
    for(int i=1;i<=ent-level;i++)
    {
        cout<<setw(4)<<" ";
    }
    for(int j=1;j<=level*2-1;j++)
    {
        cout<<setw(4)<<k;
        k++;
    }

 cout<<endl;
}

    return 0;
}






















