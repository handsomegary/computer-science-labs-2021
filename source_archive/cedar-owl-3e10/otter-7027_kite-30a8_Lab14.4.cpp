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
void reverse_str::set_string(string str1)
{
    str0=str1;
}
 void reverse_str::print_string()
 {
     cout<<str0<<endl;
 }
 void reverse_str::reverse_string()
 {
     char hold;
     for(int i=0;i<str0.length()/2;i++)
     {
         hold=str0[i];
         str0[i]=str0[str0.length()-1-i];
         str0[str0.length()-1-i]=hold;
     }
 }

int main(void)
{
    cout<<"Please enter a string:"<<endl;
    string input;
    getline(cin,input);
    cout<<endl;
    reverse_str str;
    str.set_string(input);
    str.reverse_string();
    cout<<"After reversed, the string is:"<<endl;
    str.print_string();

}
