#include <iostream>

using namespace std;






int main()
{long long int val=2;
  cout <<"Enter a number: ";
  cin >> val;
  while (val<2)
    {
     cout<<"Please enter a correct number: ";
     cin>> val;
    }
//
  cout<<val<<" = ";
  while(val%2==0)
  {
    val/=2;
    cout<<"2*";
  }
   while(val%3==0)
  {
    val/=3;
    cout<<"3*";
  }
   while(val%5==0)
  {
    val/=5;
    cout<<"5*";
  }
   while(val%7==0)
  {
    val/=7;
    cout<<"7*";
  }
  while(val%11==0)
  {
    val/=11;
    cout<<"11*";
  }
  while(val%13==0)
  {
    val/=13;
    cout<<"13*";
  }
   while(val%17==0)
  {
    val/=17;
    cout<<"17*";
  }
  cout<<"\b \b";
  }







