#include <iostream>

using namespace std;
long long int a,temp;
int i;
int b;
int x;
int z=1;
int k;
int n;
int main()
{
    cout<<"Enter the size of the diamond: ";
    cin>>a;
    temp=a;
    k=(a-2);
    n=2;
    while(a<3 or a>4294967296){
        cout<<"Enter again: ";
        cin>>a;
        temp=a;
        k=(a-2);
    }
    for(i=1;i<=a;i++){
        if(i<=((a+1)/2)){
            for(b=(temp+1)/2;b>0;b--){
            cout<<"*";
            }
            for(int c=1;c<=z;c++){
            cout<<" ";
            }
            for(b=(temp+1)/2;b>0;b--){
                cout<<"*";
            }
            z+=2;
            temp-=2;
            
        }
    
        if(i>((a+1)/2)){


            for(int m=1;m<=n;m++){
                cout<<"*";

            }
            for(int g=1;g<=k;g++){
                cout<<" ";

            }
            for(int m=1;m<=n;m++){
             cout<<"*";

            }
            n++;
            k=k-2;
        }
        cout<<endl;
    }

    }











