#include <iostream>
#include <ctime>
#include<cmath>
#include<iomanip>
using namespace std;

int main()
{
    unsigned int sample;
    cout << "Enter # of sample: " << endl;
    cin >>sample;
    srand(time(0));
    unsigned int A=0,B=0,C=0,D=0,F=0;
    for(int i=1;i<=sample;i++){
        int a=(rand()%100)+1;
        if(a>=90 and a<=100)
            A++;
        if(a>=80 and a<=89)
            B++;
        if(a>=70 and a<=79)
            C++;
        if(a>=60 and a<=69)
            D++;
        if(a>=0 and a<=59)
            F++;


    }

    cout<<"A: "<<A<<endl;
    cout<<"B: "<<B<<endl;
    cout<<"C: "<<C<<endl;
    cout<<"D: "<<D<<endl;
    cout<<"F: "<<F<<endl;

    float mean;
    float stdev;
    mean=(A*95+B*84.5+C*74.5+D*64.5+F*29.5)/sample;
    cout<<"Mean: "<<fixed<<setprecision(2)<<mean<<endl;
    stdev=sqrt((A*95*95+B*84.5*84.5+C*74.5*74.5+D*64.5*64.5+F*29.5*29.5)/sample-mean*mean);
    cout<<"STD Deviation: "<<fixed<<setprecision(2)<< stdev<<endl;






    return 0;
}
