#include <iostream>
#include<string>
using namespace std;
struct example
{
    string str1;
    string str2;


}a;

int main()
{
    int digits=0;
    cout<<"Please enter a string."<<endl;
    getline(cin,a.str1);
    cout<<"str1 = "<<a.str1<<endl;

    a.str2=a.str1;
    for(int i=0;i<a.str1.length();i++){
        if(a.str1[i]=='0' || a.str1[i]=='1'|| a.str1[i]=='2' || a.str1[i]=='3' || a.str1[i]=='4' || a.str1[i]=='5' || a.str1[i]=='6' || a.str1[i]=='7' || a.str1[i]== '8'|| a.str1[i]=='9'){
            digits++;
            a.str2[i]='*';


        }
    }
    cout<<"The number of the digits in the str1 is "<<digits<<"."<<endl;
    cout<<"str2 = "<<a.str2;





    return 0;
}
