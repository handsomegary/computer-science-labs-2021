#include <iostream>
#include <cstdlib>
#include <ctime>
#include<cmath>
#include<iomanip>

using namespace std;
char grade(int);
double stdev(double,double);

int main()
{
    int sample,a=0,b=0,c=0,d=0,f=0,randon,sum=0,square=0;
    double average,square_average;
    srand(time(NULL));
    cout << "Enter # of sample: ";
    cin>>sample;
    for(int i=1;i<=sample;i++)
    {
        randon=rand()%100+1;
        sum+=randon;
        square+=randon*randon;
        switch(grade(randon))
        {
            case 'A':a++;
                break;
            case 'B':b++;
                break;
            case 'C':c++;
                break;
            case 'D':d++;
                break;
            case 'F':f++;
                break;
        }
    }
    average=sum/sample;
    square_average=square/sample;
    cout<<"A: "<<a<<endl;
    cout<<"B: "<<b<<endl;
    cout<<"C: "<<c<<endl;
    cout<<"D: "<<d<<endl;
    cout<<"F: "<<f<<endl;
    cout<<"Mean: "<<setprecision(2)<<fixed<<average<<endl;
    cout<<"STD Deviation: "<<setprecision(2)<<fixed<<stdev(square_average,average)<<endl;

    return 0;

}
char grade(int a)
{
    if(a<=100&&a>=90)
        return 'A';
    else if(a>=80)
        return 'B';
    else if(a>=70)
        return 'C';
    else if(a>=60)
        return 'D';
    else
        return 'F';
}
double stdev(double s,double a)
{
    return sqrt(s-a*a);
}
