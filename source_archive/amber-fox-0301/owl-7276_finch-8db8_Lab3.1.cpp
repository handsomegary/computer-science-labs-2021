#include <iostream>

using namespace std;

int main()
{
    int a,b,c;
    cout << "Please enter 3 different integers: " << endl;
    cin>>a;
    cin>>b;
    cin>>c;
     if(a>b&&b>c)
    cout<<"The sorting result from small to large is "<<c<<"->"<<b<<"->"<<a;
     if(a>c&&c>b)
    cout<<"The sorting result from small to large is "<<b<<"->"<<c<<"->"<<a;
     if(b>a&&a>c)
    cout<<"The sorting result from small to large is "<<c<<"->"<<a<<"->"<<b;
     if(b>c&&c>a)
    cout<<"The sorting result from small to large is "<<a<<"->"<<c<<"->"<<b;
     if(c>a&&a>b)
    cout<<"The sorting result from small to large is "<<b<<"->"<<a<<"->"<<c;
     if(c>b&&b>a)
    cout<<"The sorting result from small to large is "<<a<<"->"<<b<<"->"<<c;
    return 0;
}

