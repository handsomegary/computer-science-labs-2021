#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main()
{
    cout << "Please enter the scores of three students:" << endl;

    int a[3];


    for(int i=0;i<3;i++){
        cin>>a[i];

    }
    float average;
    average=((float)a[0]+(float)a[1]+(float)a[2])/3;

    cout<<"avg = "<<fixed<<setprecision(3)<<average<<endl;






    if(a[0]<60 or a[1]<60 or a[2]<60){
        cout<<"fail:"<<endl;

        for(int i=0;i<3;i++){
            if(a[i]<60){
                cout<<(i+1)<<": "<<a[i]<<endl;

            }

        }


    }





    return 0;
}
