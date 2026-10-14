#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    int howmany=0,failed=0,score;
    cout<<"Please enter the input file name:"<<endl;
    string fn;
    cin>>fn;
    ifstream inFile(fn,ios::in);

    if(!inFile.is_open()){
        cout<<"File could not be opened.";
        exit(0);
    }

    while(inFile>>score){
        howmany++;
        if(score<60)
            failed++;
    }
    cout<<howmany<<endl;
    cout<<failed;



    return 0;
}
