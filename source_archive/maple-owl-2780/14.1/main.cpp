#include <iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
    string a;
    cout<<"Please enter the arithmetic:";
    cin>>a;
    int ccc[a.length()]={0};
    vector<int>b;int bi=0;
    vector<int>c;int ci=0;
    for(int i=0;i<a.length();i++){
        if(a[i]=='*' || a[i]=='/'  ||a[i]=='%')
            ccc[i]=2;

    }
    for(int i=0;i<a.length();i++){
        if(a[i]=='+' || a[i]=='-' )
            ccc[i]=1;
    }
    int sum=0;










    return 0;
}
