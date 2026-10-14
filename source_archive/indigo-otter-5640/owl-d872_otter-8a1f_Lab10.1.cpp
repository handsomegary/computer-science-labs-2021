#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
void reverse(void);
void swap(long long *const, long long *const);
int list = 1;

int main()
{
    long long int a[51] = {0}, b[51] = {0};
    while(true)
    {
        cin >> a[list];
        list++;
        char ch = getchar();
        if(ch == '\n')
        {
            break;
        }
    }
    swap(a,b);
    for(int i = 50 - list + 1; i < 50; i++)
    {
        cout << b[i] <<" ";
    }
    return 0;
}

void swap(long long int *a1,long long int *a2 )
{
    for(int i = 1; i <= list; i++)
    {
        *(a2 + 50 - i) = *(a1 + i);
    }
}

void reverse()
{
    list = 0;
}
