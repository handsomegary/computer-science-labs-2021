#include <iostream>

using namespace std;
double ro(long long int a , double b=1.0);
int look(long long int a);
double ro10(long long int a,double b,int c,double d=10,double e=0);
int main()
{
    long long int a;
    cout<<"Enter a number: ";
    cin>>a;
    while(a<0){
        cout<<"The number is out of range. Please enter again: ";
        cin>>a;
    }
    
    return 0;
}
int look(long long int a){
	if(a/10>0)
		return 1+look(a/10);
	if(a/10==0)
		return 1;
}
double ro(long long int a,double b){
		if(a>(b*b)){
			return(ro(a,b+1))
		}
		else
			return b;
	
}
double ro10(long long int a,double b,int c,double d,double e){
		
		
		
		if(a>(b+e/d)*(b+e/d) && c>0)
			return ro10(a,b,c,d,e+1);
		else(a<(b+e/d)*(b+e/d) && c>0)
			return ro10(a,(b+e)/d,c-1,d*10,0);
		if(c==0){
			
			return (b+e/d);
		}
	
	
}
