#include <iostream>

using namespace std;
struct driver
{
    int distance;
    int fine;
};
int main()
{
    int n,d,r;
    int number;
    while(1)
    {
        cin>>n>>d>>r;
        if(n==0&&d==0&&r==0)
            break;
        driver calculate;
        calculate.distance=0;
        calculate.fine=0;

        while(1)
        {
            cin>>number;
            calculate.distance+=number;
            if(getchar()=='\n')
                break;
        }
        while(1)
        {
            cin>>number;
            calculate.distance+=number;
            if(getchar()=='\n')
                break;
        }
        if(calculate.distance<=n*d)
        {
            cout<<calculate.fine<<endl;
        }
        else
        {
            calculate.fine=(calculate.distance-n*d)*r;
            cout<<calculate.fine<<endl;
        }


    }
    return 0;
}
