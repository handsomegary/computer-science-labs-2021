#include <iostream>
#include<iomanip>
using namespace std;

double rf(double,double,double ,double );

int main()
{
    double a0;
    cout << "Enter a number: " ;
    cin>>a0;
    while(a0<0){
        cout<<"The number is out of range. Please enter again: ";
        cin>>a0;
    }
    cout<<fixed<<setprecision(10)<<rf(a0,1,0,0);
    return 0;
}
double rf(double a,double aa,double counter,double root){
    if(counter>10)
        return root;
    if(a>root*root)
        return rf(a,aa,counter,root+aa);
    if(a==root*root)
        return root;
    if(root*root>a){
        root-=aa;
        aa/=10;
        return rf(a,aa,++counter,root+aa);
    }


}
