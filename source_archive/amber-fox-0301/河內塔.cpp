#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


void arange(int disk,int depart,int terminal)
{
    int temp;
    switch (depart+terminal)
    {
        case 3:temp=3;break;
        case 4:temp=2;break;
        default:temp=1;break;
    }
    if(disk==1) cout<<depart<<" ---> "<<terminal<<endl;

    else
    {
     arange(disk-1,depart,temp);
     cout<< depart <<" ---> "<< terminal<<endl;
     arange(disk-1,temp,terminal);

    }

}
int main()
{
int disk;
cout<<"Please enter the number: ";
cin>>disk;

arange(disk,1,3);

return 0;
}
