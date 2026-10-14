#include <iostream>

using namespace std;
void reverse();
void swap(long long *const, long long *const);
long long int a[50]={0};
long long int n;
int i=0;
int main()
{
    reverse();
    for(int m=0;m<=i;m++){

        cout<<a[m]<<" ";
    }


    return 0;
}
void reverse(){

    while(cin>>n){
        a[i]=n;
        if(cin.get()=='\n')
            break;
        i++;
    }
    for(int j=0;j<=i/2;j++){
        swap(&a[j],&a[i-j]);
    }


}
void swap(long long *const x, long long *const y){
    long long int temp;
    temp=*x;
    *x=*y;
    *y=temp;


}
