#include<iostream>
#include<iomanip>
using namespace std;
int row;
int w;
int a;
int c=1;
int count=1;
int main(){
	cout<<"Enter number of rows: ";
	cin>>row;

	w=1+2*(row-1);
	a=(w-1)/2;
	for(int i=1;i<=row;i++){
		for(int j=1;j<=a;j++){
				cout<<setw(4)<<" ";

		}
		for(int h=1;h<=c;h++){
				cout<<setw(4)<<count;
				count++;
			}
		for(int j=a+c;j<=w;j++){
				cout<<setw(4)<<" ";

		}




		c+=2;

		a--;
		cout<<endl;

	}




	return 0;
}
