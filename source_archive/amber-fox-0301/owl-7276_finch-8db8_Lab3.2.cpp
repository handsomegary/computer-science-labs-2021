#include <iostream>

using namespace std;


long long int func1(int n)
    {
      if(n<=1)
    return 1;
    else
        return(n*func1(n-1));
    }



int main()
{
    int N;
    cout<< "Please enter a nonnegative integer: ";
    cin>> N ;
    cout<< "The corresponding factorial is "<<func1(N);


    return 0;
}
