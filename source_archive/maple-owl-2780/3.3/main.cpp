#include <iostream>
#include <math.h>
using namespace std;











int main()
{
    unsigned int a[20];
    unsigned int b;
    unsigned int i=0;
    int sum=0;


    cout<<"Please input an unsigned binary number: ";
    cin>>b;
    while(1){
       if(b%10==0){
            a[i]=0;
            b/=10;
            i++;

       }


       if(b%10==1){
            a[i]=1;
            b/=10;
            i++;
       }
       if(b==0){
            a[i]=-1;
            break;

       }
    }
    i=0;
        while(a[i]!=-1){
               sum=a[i]*pow(2,i)+sum;
               i++;

            if(a[i]==a[20])
                break;





        }

    cout<<"The corresponding decimal number is "<<sum;


    return 0;
}
