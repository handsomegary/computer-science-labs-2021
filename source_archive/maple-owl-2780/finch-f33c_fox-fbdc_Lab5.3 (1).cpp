#include <iostream>

using namespace std;
int  a,b,Cin,sum,Co;

int main()
{   while(1){
        cout<<"Enter a: ";
        cin>>a;
        if(a==-1){
            break;
        }
        cout<<"Enter b: ";
        cin>>b;
        cout<<"Enter Cin: ";
        cin>>Cin;


        if(a!=1){
            if(a!=0){
                cout<<"!!! Enter the inputs again !!!"<<endl;
                continue;
            }
        }
        if(b!=1){
            if(b!=0){
                cout<<"!!! Enter the inputs again !!!"<<endl;
                continue;
            }
        }
        if(Cin!=1){
            if(Cin!=0){
                cout<<"!!! Enter the inputs again !!!"<<endl;
                continue;
            }
        }
        switch(a*b*Cin==0 || a*b*Cin==1){
        case 1:
            break;
        default:
            cout<<"!!! Enter the inputs again !!!"<<endl;
            continue;
        }
        cout<<"--------------------"<<endl;
        cout<<"  A  B  Cin Sum Cout"<<endl;

        if(a||b||Cin==1){
            sum=1;
            if(a+b+Cin==2)
                sum=0;
        }
        else
            sum=0;

        if((a&&b)||(a&&Cin)||(b&&Cin)==1)
            Co=1;
        else
            Co=0;




    cout<<"  "<<a<<"  "<<b<<"    "<<Cin<<"   "<<sum<<"    "<<Co<<endl;
    cout<<"--------------------"<<endl;




    }
    cout<<"Bye~";
    return 0;
}
