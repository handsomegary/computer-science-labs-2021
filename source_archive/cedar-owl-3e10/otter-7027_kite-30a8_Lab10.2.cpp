#include <iostream>

using namespace std;
void find_mountain(long long int *const, int *const);
int mountain=0;
int up,low;
int main()
{
    int num=0;

    long long int number[50]= {};

    while(1)
    {
        cin>>number[num++];
        if(getchar()=='\n')
            break;
    }
    find_mountain(number,&num);
    cout<<mountain<<endl;
    for(int i=low; i<=up; i++)
        cout<<number[i]<<" ";
    return 0;
}
void find_mountain(long long int *const num, int *const length)
{
    int down[25]= {0};
    int j=0,largest=0;
    for(int i=1; i<*length-1; i++)
    {
        if(num[i]>num[i-1]&&num[i]>num[i+1])
        {
            mountain++;
        }
    }
    for(int i=1; i<*length-1; i++)
    {
        if(num[i]<num[i-1]&&num[i]<num[i+1])
        {
            down[j++]=i;

        }
    }
    down[j++]=*length-1;



    if(num[0]<num[1])
    {
        largest=down[0]-0;
        up=down[0];
        low=0;
        for(int i=0; i<j-1; i++)
        {
            if(down[i+1]-down[i]>largest)
            {
                largest=down[i+1]-down[i];
                up=down[i+1];
                low=down[i];
            }
        }
    }
    else if(num[0]>num[1])
    {
        for(int i=0; i<j-1; i++)
        {
            if(down[i+1]-down[i]>largest)
            {
                largest=down[i+1]-down[i];
                up=down[i+1];
                low=down[i];
            }
        }
    }
    else
    {
        int change=0;
        for(int i=1;i<*length;i++)
        {
            if(num[i]!=num[0])
            {
                change=i;
                break;
            }
        }
        if(num[change]>num[0])
        {
            largest=down[0]-0;
            up=down[0];
            low=0;
            for(int i=0; i<j-1; i++)
            {
                if(down[i+1]-down[i]>largest)
                {
                    largest=down[i+1]-down[i];
                    up=down[i+1];
                    low=down[i];
                }
            }
        }
        else
        {
            for(int i=0; i<j-1; i++)
            {
                if(down[i+1]-down[i]>largest)
                {
                    largest=down[i+1]-down[i];
                    up=down[i+1];
                    low=down[i];
                }
            }
        }
    }
}










