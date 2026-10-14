#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{

    int aray[400],sum,control=1;
    string filetitle;
    cout<<"File: ";
    getline(cin,filetitle);
    fstream ifile(filetitle,ios::in);
     while(!ifile.eof())
    {
    string a;
    ifile>>a;
    if(a=="prices:")break;
    }
    while(!ifile.eof())
    {
    ifile>>aray[control];
    control++;
    }
    for(int i=1;i<control;i++)
    {
        if(aray[i+1]>aray[i])sum+=(aray[i+1]-aray[i]);
    }
    cout<<"Maximum profit: "<<sum;
    return 0;
}

