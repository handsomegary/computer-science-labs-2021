#include <iostream>
using namespace std;

int main()
{
    int x;
    int y;
    int z;
    cout << "Please enter 3 different integers: " << endl;
    cin >> x ;
    cin >> y ;
    cin >> z ;

    if(x>y&&y>z)
    cout << "The sorting result from small to large is " << z << "->" << y << "->" << x;
    else if(x>z&&z>y)
    cout << "The sorting result from small to large is " << y << "->" << z << "->" << x;
    else if(y>x&&x>z)
    cout << "The sorting result from small to large is " << z << "->" << x << "->" << y;
    else if(y>z&&z>x)
    cout << "The sorting result from small to large is " << x << "->" << z << "->" << y;
    else if(z>y&&y>x)
    cout << "The sorting result from small to large is " << x << "->" << y << "->" << z;
    else if(z>x&&x>y)
    cout << "The sorting result from small to large is " << y << "->" << x << "->" << z;
    return 0;
}
