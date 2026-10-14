#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    int sample,a=0,b=0,c=0,d=0,f=0,grade;double ave1,ave2;long long int tot1=0,tot2=0;
    cout << "Enter # of sample: ";cin>>sample;

    for(int i=1;i<=sample;i++)
    {

        grade=rand()%101;
        switch (grade/10)
        {
         case 10: a++;break;
        case 9 : a++;break;
        case 8 : b++;break;
        case 7 : c++;break;
        case 6 : d++;break;
        default: f++;
        }

        tot1+=grade;
        tot2+=grade*grade;
    }
    ave1=tot1/sample;
    ave2=tot2/sample;

    cout<<"A: "<<a<<endl;
    cout<<"B: "<<b<<endl;
    cout<<"C: "<<c<<endl;
    cout<<"D: "<<d<<endl;
    cout<<"F: "<<f<<endl;
    cout<<"Mean: "<<ave1<<endl;
    cout<<"STD Deviation: "<<setprecision(4) << sqrt(ave2-ave1*ave1);



    return 0;
}
