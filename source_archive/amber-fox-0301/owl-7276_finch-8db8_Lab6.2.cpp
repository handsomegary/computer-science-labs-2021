#include <iostream>
#include<cmath>

using namespace std;


void rectangleArea(int a1,int a2)
{
    cout<<a1*a2;
}
void rectanglePerimter(int a1,int a2)
{
    cout<<(a1+a2)*2;
}
void triangleArea(double a1,double  a2,double  a3)
{
    double s;
    s=(a1+a2+a3)/2;

    double area= pow(s*(s-a1)*(s-a2)*(s-a3),0.5);
    int co=pow(s*(s-a1)*(s-a2)*(s-a3),0.5);
    if(area>co+0.5)cout<<co+1;
        else cout<<co;

}
void traianglePerimeter(int a1,int a2,int a3)
{
    cout<<a1+a2+a3;
}



int main()
{ int a1,a2,a3,k;
cout<<"Input 3 Numbers: ";
cin>>a1;
cin>>a2;
cin>>a3;
if(a1+a2<=a3||a1+a3<=a2||a2+a3<=a1)k=1;
else
    {
        if(a1-a2>=a3||a1-a3>=a2||a2-a3>=a1)k=1;
        else k=0;
    }
while(k==1)
{   cout<<"error"<<endl;
    cout<<"Input 3 Numbers: ";
    cin>>a1;
    cin>>a2;
    cin>>a3;
    if(a1+a2<=a3||a1+a3<=a2||a2+a3<=a1) k=1;
    else
    {
        if(a1-a2>=3||a1-a3>=a2||a2-a3>=a1)k=1; else k=0;
    }
}
cout<<"Perimeter of the rectangle: ";rectanglePerimter(a1,a2);cout<<endl;
cout<<"Area of the rectangle: ";rectangleArea(a1,a2);cout<<endl;
cout<<"Perimeter of the triangle: ";traianglePerimeter(a1,a2,a3);cout<<endl;
cout<<"Area of the triangle: "; triangleArea(a1,a2,a3);cout<<endl;
    return 0;
}
