#include <iostream>

using namespace std;

int main()
{
    int number;
    cout<<"Enter the size of the diamond: ";
    cin>>number;
    while(number<3)
    {
        cout<<"Enter again: ";
        cin>>number;
    }
    int c=(number+3)/2;
    int cc=(number+1)/2-1;
    for(int i=0;i<number;i++)
    {
        for(int j=1;j<=number+2;j++)
        {
            if(i<=cc)
                if(j<=c+i&&j>=c-i)
                    cout<<" ";
                else
                    cout<<"*";
            else
                if(j<=c+(number-i-1)&&j>=c-(number-i-1))
                    cout<<" ";
                else
                    cout<<"*";

        }
        cout<<endl;
    }
    return 0;
}
