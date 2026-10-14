#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;
void rectangleArea(int ,int);
void rectanglePerimeter(int, int);
void triangleArea(double,double,double);
void trianglePerimeteint(int,int,int);

int main(void)
{
    int a,b,c;
    cout<<"Input 3 Numbers: ";
    cin>>a>>b>>c;
    while(a+b<=c||a+c<=b||b+c<=a)
    {
        cout<<"error"<<endl;
        cout<<"Input 3 Numbers: ";
        cin>>a>>b>>c;
    }
    rectanglePerimeter(a, b);
    rectangleArea(a ,b);

    trianglePerimeteint(a,b,c);
    triangleArea(a,b,c);
    return 0;

}
void rectangleArea(int x ,int y)
{
    cout<<"Area of the rectangle: "<<x*y<<endl;
}
void rectanglePerimeter(int x, int y)
{
    cout<<"Perimeter of the rectangle: "<<(x+y)*2<<endl;
}
void triangleArea(double x,double y,double z)
{
    double s=(x+y+z)/2;

    double area=sqrt(s*(s-x)*(s-y)*(s-z));

    cout<<"Area of the triangle: "<<setprecision(0)<<fixed<<area<<endl;
}
void trianglePerimeteint(int x,int y,int z)
{
    cout<<"Perimeter of the triangle: "<<x+y+z<<endl;
}
