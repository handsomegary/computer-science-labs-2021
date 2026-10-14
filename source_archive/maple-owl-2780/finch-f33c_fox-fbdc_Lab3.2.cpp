#include <iostream>

using namespace std;

long factorial(int n){
    if(n==0)
        return 1;
    if(n>0)
        return n*factorial(n-1);


}



int main()
{
    int n;

    cout<<"Please enter a nonnegative integer: ";
    cin>>n;
    if(n<=20 && n>=0)
        cout<<"The corresponding factorial is "<<factorial(n);








    return 0;
}
