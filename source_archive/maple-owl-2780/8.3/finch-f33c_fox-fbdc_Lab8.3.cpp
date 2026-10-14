#include <iostream>

using namespace std;

int main()
{

    int a;
    while(1){
        cout << "Please enter a number for the column of the Pascal triangle:" << endl;
        cin>>a;
        if(a==0)
            break;
        int p[a][a];
        for(int x=0;x<a;x++){
            p[x][0]=1;
            p[x][x]=1;

        }
        if(a>2){
            for(int x=2;x<a;x++){
                for(int i=1;i<x;i++){
                    p[x][i]=p[x-1][i-1]+p[x-1][i];
                }
            }
        }
        for(int i=0;i<a;i++){
            for(int j=0;j<=i;j++){
                    cout<<p[i][j];
                    cout<<"  ";

            }
            cout<<endl;




        }
    cout<<endl;



    }
    return 0;
}
