#include <iostream>
#include<iomanip>

using namespace std;

int main()
{
    int a[3],fail=0;
    double ave=0;
    cout << "Please enter the scores of three students: "<<endl;
    for(int i=0;i<3;i++)
        cin>>a[i];
    for(int i=0;i<3;i++)
    {
        if(a[i]<60)
        fail++;

    }
    for(int i=0;i<3;i++)
     {
          ave+=a[i];

     }
    cout<<"avg = "<<setprecision(3)<<fixed<<ave/3<<endl;
    if(fail>0)
        cout<<"fail:"<<endl;
    for(int i=0;i<3;i++)
    {
        if(a[i]<60)
            cout<<i+1<<": "<<a[i]<<endl;
    }
    return 0;
}
