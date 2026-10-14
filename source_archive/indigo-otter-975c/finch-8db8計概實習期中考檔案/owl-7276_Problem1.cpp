#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int head,leg;double click;
while(true)
{
    cin>>head>>leg;
    click=2*head-leg/2;
    if(head==0&&leg==0)break;
    if(click<0||head-click<0) cout<<"no"<<endl;
    else if(leg%2==1) cout<<"no"<<endl;
    else{
     cout<<"Chick "<<click<<" Rabbit "<<head-click<<endl;
    }


}
    cout<<"Bye";
    return 0;
}
