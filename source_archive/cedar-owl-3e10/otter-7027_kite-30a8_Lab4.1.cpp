#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int number;
    int i=2;
    vector <int> p;
    cout<<"Enter a number: ";
    cin>>number;
    while(number<2)
    {
        cout<<"Please enter a correct number: ";
        cin>>number;
    }
    int number1=number;
    while(number!=1)
    {
        if(number%i==0)
        {
            number/=i;
            p.push_back(i);
            continue;
        }
        i++;
    }
    int c=p.size();
    int d=p.size();
     i=0;
    cout<<number1<<" = ";
    while(i<d)
    {
        if(c!=1)
        {
            cout<<p[i]<<"*";
            c--;
        }
        else
        cout<<p[i];
        i++;
    }
    cout<<endl;
    return 0;
}
