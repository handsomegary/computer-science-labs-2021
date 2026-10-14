#include <iostream>
#include <iomanip>
using namespace std;


int xo(int a, int b)
{
    if(a==b) return 1;
    else return 0;
}

int an(int a, int b)
{
    if(a==0||b==0) return 0;
    else return 1;
}
int main()
{
 int a, b, ab, ci, co,s;
 while(a!=-1||b!=-1||ci!=-1)
  {

    cout<<"Enter a: ";cin>>a;if(a==-1)break;
    cout<<"Enter b: ";cin>>b;if(b==-1)break;
    cout<<"Enter Cin: ";cin>>ci;if(ci==-1)break;

    while(a!=1&&a!=0)
    {
    cout<<"!!! Enter the inputs again !!!"<<endl;
    cout<<"Enter a: ";cin>>a;if(a==-1)break;
    cout<<"Enter b: ";cin>>b;if(b==-1)break;
    cout<<"Enter Cin: ";cin>>ci;if(ci==-1)break;

    }
     while(b!=1&&b!=0)
    {

   cout<<"!!! Enter the inputs again !!!"<<endl;
    cout<<"Enter a: ";cin>>a;if(a==-1)break;
    cout<<"Enter b: ";cin>>b;if(b==-1)break;
    cout<<"Enter Cin: ";cin>>ci;if(ci==-1)break;
    }
     while(ci!=1&&ci!=0)
    {

   cout<<"!!! Enter the inputs again !!!"<<endl;
    cout<<"Enter a: ";cin>>a;if(a==-1)break;
    cout<<"Enter b: ";cin>>b;if(b==-1)break;
    cout<<"Enter Cin: ";cin>>ci;if(ci==-1)break;
    }
    if(a==-1||b==-1||ci==-1)break;
    s=xo(xo(a,b),ci);
    co=an(a,b)+an(b,ci)+an(a,ci);
    if (co>0) co=1;
    else co=0;

    cout<<"--------------------"<<endl;
    cout<<"  A  B  Cin Sum Cout"<<endl;
    cout<<setw(3)<<a;
    cout<<setw(3)<<b;
    cout<<setw(5)<<ci;
    cout<<setw(4)<<s;
    cout<<setw(5)<<co<<endl;
    cout<<"--------------------"<<endl;
     s=0;
     co=0;
  }



    cout<<"Bye~ ";
    return 0;


}
