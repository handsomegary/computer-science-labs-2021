#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
    int aray[8]={0};
    int disp[8]={0};
    for(int i=1;i<=7;i++)
    {
        cin>>aray[i];
    }
    if(aray[4]<aray[5]){disp[1]=aray[4];disp[2]=aray[5];}
    else{disp[2]=aray[4];disp[1]=aray[5];}
    if(aray[2]<aray[3]){disp[3]=aray[2];disp[6]=aray[3];}
    else{disp[6]=aray[2];disp[3]=aray[3];}
    if(aray[6]<aray[7]){disp[4]=aray[6];disp[5]=aray[7];}
    else{disp[5]=aray[6];disp[4]=aray[7];}
    disp[7]=aray[1];
    for(int i=1;i<=7;i++)
    {
        cout<<disp[i]<<' ';
    }
    return 0;
}

