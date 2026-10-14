#include <iostream>

using namespace std;



int main()
{
    int prime_array[5135]= {0};
    bool flag;
    int index=1;
    int n;
    int count=0;

    for(int num=2; num<=50000; num++)
    {
        flag=true;
        for(int i=1; i<index; i++)
        {

            if(prime_array[i]*prime_array[i]>num)
            {

                break;
            }


            if(num%prime_array[i]==0)
            {
                flag= false;
                break;
            }
        }
        if(flag==true)
            prime_array[index++]=num;

    }
    cout<<"Input number: ";
    cin>>n;
    for(int i=1; prime_array[i]<=n/2; i++)
    {

        int low_index = 0;
        int high_index=index;
        int mid_index;
        bool flag=false;
        while(low_index<=high_index)
        {
            mid_index = (low_index + high_index)/2;
            if( prime_array[mid_index] == n-prime_array[i] )
            {
                flag = true;
                break;
            }
            else if ( prime_array[mid_index] < n-prime_array[i])
            {
                low_index = mid_index + 1;
            }
            else
            {
                high_index = mid_index -1;
            }
        }
        if(flag==true)
            count++;


    }
    cout<<"Number of combinations: "<<count;
}
