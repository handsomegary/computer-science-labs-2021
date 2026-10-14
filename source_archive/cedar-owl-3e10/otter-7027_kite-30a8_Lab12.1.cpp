#include <iostream>
#include<string>
#include<fstream>

using namespace std;

int main()
{
    string filename;
    int score[100]={0};
    int num=1,fail=0;
    cout<<"Please enter the input file name:"<<endl;
    cin>>filename;
    fstream inputfile(filename,ios::in);
    if(!inputfile)
    {
        cout << "File could not be opened. "<<endl;
        exit(0);
    }
    while(inputfile>>score[num++])
    {

    }
    cout<<num-2<<endl;
    for(int i=1;i<num-1;i++)
    {
        if(score[i]<60)
            fail++;
    }
    cout<<fail;
    return 0;
}
