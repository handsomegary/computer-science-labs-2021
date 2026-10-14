//14_4
#include <iostream>
#include <string>
using namespace std;

class reverse_str
{
public:
    void set_string(string);
    void print_string();
    void reverse_string();

private:
    string str0;
};
void reverse_str::print_string(){
	cout<<str0;
}
void reverse_str::reverse_string(){
	string temp = str0;
	int s=temp.length();
	for(int i=0;i<s;i++){
		str0[i]=temp[s-1-i];
	} 
}
void reverse_str::set_string(string a){
	str0=a;
}


int main(){
	reverse_str r;
	string str;
	cout<<"Please enter a string:"<<endl;
	getline(cin,str);
	r.set_string(str);
	r.reverse_string();
	cout<<endl;
	cout<<"After reversed, the string is:"<<endl;
	r.print_string();
	
}
