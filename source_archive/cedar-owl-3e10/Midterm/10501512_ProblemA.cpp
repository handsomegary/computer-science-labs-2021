#include <iostream>

using namespace std;

int main()
{
    int x,y;
    double chick,rabbit;
    do
    {

        cin>>x>>y;
        chick=(4*x-y)/2;
        rabbit=(y-2*x)/2;
        if(x!=0||y!=0)
            if(((4*x-y)%2==0)&&((y-2*x)%2==0))
                cout<<"Chick "<<chick<<" Rabbit "<<rabbit<<endl;
            else
                cout<<"no"<<endl;
        else
        {
            cout<<"Bye"<<endl;
            break;
        }

    }while(x!=0||y!=0);
    return 0;
}
