#include <iostream>
#include <math.h>
using namespace std;

void triangleArea(double x, double y, double z)
{
    double s;
    s = (x + y + z)/2;
    int trianglearea = pow(s*(s-x)*(s-y)*(s-z),0.5);
    if(pow(s*(s-x)*(s-y)*(s-z),0.5) > trianglearea + 0.5)
    {
        cout << trianglearea+1;
    }
    else
    {
        cout << trianglearea;
    }

}
void trianglePerimeter(int x, int y, int z)
{
    cout << x + y + z;
}
void rectangleArea(int x, int y)
{
    cout << x*y;
}
void rectanglePerimeter(int x, int y)
{
    cout << 2*(x+y);
}

int main()
{
    int a, b, c;
    cout << "Input 3 Numbers: ";
    cin >> a >> b >> c;
    while(a + b <= c || b + c <= a || a + c <= b)
    {
        cout << "error" << endl << "Input 3 Numbers: ";
        cin >> a >> b >> c;
    }
    cout << "Perimeter of the rectangle: " ;rectanglePerimeter(a,b);cout << endl;
    cout << "Area of the rectangle: " ;rectangleArea(a,b);cout << endl;
    cout << "Perimeter of the triangle: ";trianglePerimeter(a, b, c);cout << endl;
    cout << "Area of the triangle: " ;triangleArea(a, b, c);cout << endl;
    return 0;
}
