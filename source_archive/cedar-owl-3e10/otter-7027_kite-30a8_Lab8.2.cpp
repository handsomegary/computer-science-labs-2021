#include <iostream>

using namespace std;

int main()
{
    int a1,d,n,sum=0;
    cout << "Please enter the first term(a1), the common difference(d) and the number of terms(n):" << endl;
    cin>>a1>>d>>n;
    int s[n]={a1};
    for(int i=1;i<n;i++)
    {
        s[i]=s[i-1]+d;
    }
    cout<<"The arithmetical series: ";
    for(auto t:s)
    {
        sum+=t;
        if(t!=s[n-1])
        {
             if(t<0)
                cout<<"("<<t<<")";
            else
                cout<<t;
            cout<<" + ";
        }
        else
        {
             if(t<0)
                cout<<"("<<t<<")";
            else
                cout<<t;
        }


    }
    if(sum<0)
        cout<<" = ("<<sum<<")"<<endl;
    else
        cout<<" = "<<sum<<endl;

    return 0;
}
