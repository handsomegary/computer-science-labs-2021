#include <iostream>

using namespace std;

int main()
{
    int a=0,b=0,c=0,Sum,Cout;
    while(a!=-1)
    {
        do
        {
            if((a!=-1&&a!=0&&a!=1)||(b!=0&&b!=1)||(c!=0&&c!=1))
                cout<<"!!! Enter the inputs again !!!"<<endl;
            cout<<"Enter a: ";
            cin>>a;
            if(a==-1)
            {   cout<<"Bye~";
                break;
            }
            cout<<"Enter b: ";
            cin>>b;
            cout<<"Enter Cin: ";
            cin>>c;
        }while((a!=-1&&a!=0&&a!=1)||(b!=0&&b!=1)||(c!=0&&c!=1));
        if(a==-1)
        {
            break;
        }
        Sum=a^b^c;
        Cout=((a^b)&&c)||(a&&b);

        cout<<"--------------------"<<endl;
        cout<<"  A  B  Cin Sum Cout"<<endl;
        cout<<"  "<<a<<"  "<<b<<"    "<<c<<"   "<<Sum<<"    "<<Cout<<endl;
        cout<<"--------------------"<<endl;

    }
    return 0;
}
