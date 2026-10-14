#include <iostream>

using namespace std;

int main()
{

    int first;
    int d;
    int n;
    cout << "Please enter the first term(a1), the common difference(d) and the number of terms(n):" << endl;
    cin>>first>>d>>n;
    int a[n];
    for(int i=0;i<n;i++){
        a[i]=first+i*d;

    }
    cout<<"The arithmetical series: ";

    for(int i=0;i<n;i++){
        if(a[i]>=0)
            cout<<a[i];
        else
            cout<<"("<<a[i]<<")";
        if(i<n-1)
            cout<<" + ";

    }
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=a[i];


    }
    if(sum>=0)
        cout<<" = "<<sum;
    else
    cout<<" = "<<"("<<sum<<")";
    return 0;
}
