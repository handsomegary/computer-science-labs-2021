#include <iostream>

using namespace std;

void func1(int &val,int i)
 {
    while(val%i==0)
  {
    val/=i;
    cout<<i<<"*";
  }
 }

int main()
{  int val=2,a=2;
  cout <<"Enter a number: ";
  cin>>val;
  cout<<val<<" = ";
 while(a<=val)
 {
   func1(val,a);
   a++;
 }
   cout<<"\b \b";
}












