#include <iostream>
#include<string>
#include<vector>
using namespace std;
void reverse(long long int [],int);
void swap(long long *const, long long *const);
int main()
{

    int num=0;

    long long int number[50]={};

    while(1)
    {
        cin>>number[num++];
        if(getchar()=='\n')
            break;
    }
    int s=num;




    reverse(number,s);
for(int i=0;i<s;i++)
    {
        cout<<number[i]<<" ";
    }

    return 0;
}
void reverse( long long int a[],int s)
{



    for(int i=0;i<s/2;i++)
    {
        swap(&a[i],&a[s-1-i]);
    }
}
void swap(long long *const ptr1, long long *const ptr2)
{
    long long int hold=*ptr1;
    *ptr1=*ptr2;
    *ptr2=hold;
}
