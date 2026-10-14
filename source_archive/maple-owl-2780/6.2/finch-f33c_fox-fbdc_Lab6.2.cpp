#include <iostream>
#include <cmath>
using namespace std;
void rectangleArea(long long int,long long int);
void triangleArea(long long int,long long int,long long int);
void rectanglePerimeter(long long int,long long int);
void trianglePerimeter(long long int,long long int,long long int);



int main()
{
    long long int a,b,c;
    cout<<"Input 3 Numbers: ";
    while(1){
        int tell=0;
        cin>>a>>b>>c;
        if((a+b)<=c){
            cout<<"error"<<endl;
            cout<<"Input 3 Numbers: ";
        }
        else{
            tell++;
        }
        if((a+c)<=b){
            cout<<"error"<<endl;
            cout<<"Input 3 Numbers: ";

        }
        else{
            tell++;
        }
        if((c+b)<=a){
            cout<<"error"<<endl;
            cout<<"Input 3 Numbers: ";
        }
        else {
            tell++;
        }
        if(tell==3)
            break;

    }

    rectanglePerimeter(a,b);
    rectangleArea(a,b);
    trianglePerimeter(a,b,c);
    triangleArea(a,b,c);



    return 0;
}



void rectangleArea(long long int a,long long int b){
    int area=0;
    area=a*b;

    cout<<"Area of the rectangle: "<<area<<endl;




}
void rectanglePerimeter(long long int a,long long int b){
    int peri;
    peri=2*(a+b);

    cout<<"Perimeter of the rectangle: "<<peri<<endl;


}





void triangleArea(long long int a ,long long int b ,long long int c){


    double  area,s,h;

    s=((double)a+(double)b+(double)c)/2;
    h=s*(s-a)*(s-b)*(s-c);
    area=sqrt(h);
    int bbb=floor(area);
    if(area>=(bbb+0.5))
        area=bbb+1;
    else
        area=bbb;
    cout<<"Area of the triangle: "<<area<<endl;


}
void trianglePerimeter(long long int a,long long int b,long long int c){

    int peri;
    peri=a+b+c;

    cout<<"Perimeter of the triangle: "<<peri<<endl;









}




