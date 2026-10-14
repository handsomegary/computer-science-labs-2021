//lab3.2
#include <iostream>

using namespace std;

int main()
{
    int fact,i=1;
    unsigned long long int factorial=1;
    do
    {
        cout << "Please enter a nonnegative integer: ";
        cin>>fact;

    }while(fact<0);

    while(i<=fact)
    {
        factorial*=i;
        i++;
    }
    cout<<"The corresponding factorial is "<<factorial<<endl;
    return 0;
}
