#include <iostream>

using namespace std;

int main()
{
    long long  int a;
    long long  int i=2;

    cout<<"Enter a number: ";
    cin>>a;


	while(a<=1){

    		cout<<"Please enter a correct number:";
    		cin>>a;
	}
	cout<<a<<" = ";
    while(1){
        while( a%i == 0 )
        {
        	if(a==i){
				cout<<i;
				a =a/i;
			}
			else{
            	cout << i << "*";
           		 a = a/i;
           	}

        }
        i = i+1;
        if(a==1)
        {
        	break;
  }



	}

    cout<<endl;




}
