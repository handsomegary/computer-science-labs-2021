#include <iostream>
using namespace std;

int route_assignment(int,int,int);

int main()
{
    int n, distance, rate, a[3][100]={0};
    while(true)
    {
        cin>>n>>distance>>rate;
        if(n == 0&&(distance == 0&&rate == 0))
        {
            break;
        }
        else route_assignment(n,distance,rate);
    }
    if(n>1);
    return 0;
}

int route_assignment(int n,int distance,int rate)
{
    int a[3][50],overtime=0;
    for(int i=0;i<n;i++)
    {
        cin>>a[1][i];//store the data from 0
    }
    for(int i=0;i<n;i++)
    {
        cin>>a[2][i];//store the data from 0
    }


    for(int next_element=1;next_element<n;next_element++)//sorting a in decreasing order with insertion sort.
    {
        int insertion=0;
        insertion=a[1][next_element];
        int moveitem=next_element;
        while ((moveitem>0)&&(a[1][moveitem-1]>insertion))
        {
            a[1][moveitem]=a[1][moveitem-1];
            moveitem--;
        }
        a[1][moveitem]=insertion;
     }
     if(n>1);
     for(int next_element=1;next_element<n;next_element++)//sorting a in decreasing order with insertion sort
     {
         int insertion=0;
         insertion=a[2][next_element];
         int moveitem=next_element;
         while ((moveitem>0)&&(a[2][moveitem-1]<insertion))
         {
             a[2][moveitem]=a[2][moveitem-1];
             moveitem--;
         }
         a[2][moveitem]=insertion;
     }
     for(int i=0;i<n;i++)
     {
         if((distance-a[1][i]-a[2][i])<0)
         {
            overtime+=(a[1][i]+a[2][i]-distance)*rate;
         }
     }
     cout<<overtime<<endl;
}
