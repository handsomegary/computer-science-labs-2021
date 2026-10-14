#include <iostream>
#include<vector>
using namespace std;
void sel(int *, const int, bool(*)(int, int), bool(*)(int,int));
void swap(int * const,int * const);
bool as(int,int);
bool ds(int,int);

int main()
{
    int a[20],n,counter=0,k=0;
    while(cin>>n){
        if(cin.get()=='\n')
            break;
        a[k]=n;
        k++;
        counter++;
    }
    int b[k];
    for(int i=0;i<=counter;i++){
        b[i]=a[i];
    }
    sel(b,counter,as,ds);

    for(int i=0;i<=counter;i++){
        cout<<b[i]<<" ";
    }


    return 0;
}
void sel(int * work ,const int size, bool(*aa)(int, int), bool(*bb)(int,int)){

    int sor;

    for(int i=0;i<size-1;i++){
        sor=i;

        for(int index=i+1;index<size;index++)
            if(!(*aa)(work[sor],work[index]))
                sor=index;

        swap(&work[sor],&work[i]);



    }






}
void swap(int * const pt1,int * const pt2){

    int hold = *pt1;
    *pt1=*pt2;
    *pt2=hold;
}
bool as(int m,int n){
    return m < n;
}
bool ds(int m, int n){
    return m > n;
}
