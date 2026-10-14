
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//the program is to find the fastest step of Tower of Hanoi
void arange(int disk,int depart,int terminal)
{
    int temp; char de='0',te='0';
    switch (depart+terminal)
    {
        case 3:temp=3;break;
        case 4:temp=2;break;
        default:temp=1;break;
    }
     switch(depart)
       {
        case 1: de='A';break;
        case 2: de='B';break;
        default: de='C';break;
       }

        switch(terminal)
       {
        case 1: te='A';break;
        case 2: te='B';break;
        default: te='C';break;
       }

    if(disk==1) cout<<"move disk " <<disk<<" from "<<de<<" to "<<te<<endl;

    else
    {

     arange(disk-1,depart,temp);
    cout<<"move disk " <<disk<<" from "<<de<<" to "<<te<<endl;

     arange(disk-1,temp,terminal);

    }

}
int main()
{
int disk;

cin>>disk;

arange(disk,1,3);

return 0;
}
