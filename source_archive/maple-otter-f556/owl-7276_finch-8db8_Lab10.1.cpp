#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

void reverze(void);
void swamp(long long *const,long long *const);
int digit=1;
int main()
{
    long long int araya[51]={0},arayb[51]={0};
    while(true)
    {
        cin>>araya[digit];
        digit++;
        char ch=getchar();
        if(ch=='\n')break;
    }
    swamp(araya,arayb);
    for(int i=50-digit+1;i<50;i++)
    {
        cout<<arayb[i]<<" ";
    }
    return 0;
}

void swamp(long long int *aray1,long long int *aray2 )
{
    for(int i=1;i<=digit;i++)
    {
        *(aray2+50-i)=*(aray1+i);
    }
}

void reverze()
{
    digit=0;
}
