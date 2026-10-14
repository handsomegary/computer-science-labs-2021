#include <iostream>

using namespace std;

int main()
{

    int a[3];

    cout << "Please enter 3 different integers:\n";
    for(int i=0;i<3;i++){
        cin >> a[i];
    }
    for(int c=3;c>0;c--){
        for(int i=0;i<c-1;i++){
                if(a[i]>a[i+1]){
                    int temp;
                    temp=a[i];
                    a[i]=a[i+1];
                    a[i+1]=temp;



                }

        }







    }

    cout<<"The sorting result from small to large is "<<a[0]<<"->"<<a[1]<<"->"<<a[2];


    return 0;
}
