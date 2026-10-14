#include <iostream>
#include<string>
using namespace std;

int main()
{
    string line1;
    string line2;
    cout<<"Input Line1: ";
    getline(cin,line1);
    cout<<"Input Line2: ";
    getline(cin,line2);
    for(int i=0;i<line1.length();i++){
        if(line1[i]<=122&&line1[i]>=97){
            if(i==0){
                line1[i]-=32;
            }
            else{
                if(line1[i-1]<=90 && line1[i-1]>=65)
                    continue;
                else if(line1[i-1]<=122 && line1[i-1]>=97)
                    continue;
                else
                    line1[i]-=32;
            }

        }

    }
    for(int i=0;i<line2.length();i++){
        if(line2[i]<=122&&line2[i]>=97){
            if(i==0){
                line2[i]-=32;
            }
            else{
                if(line2[i-1]<=90 && line2[i-1]>=65)
                    continue;
                else if(line2[i-1]<=122 && line2[i-1]>=97)
                    continue;
                else
                    line2[i]-=32;

            }
        }
    }
    string op;
    op=line1+" "+line2;
    cout<<"Output Line: "<<op;

    return 0;
}
