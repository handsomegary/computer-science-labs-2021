#include <iostream>
#include <fstream>
using namespace std;

fstream infile;
fstream outfile;

int main()
{
    string infilename, outfilename;
    int lucky;
    string garbage1,garbage2;
    int giftnumber[100];
    string gifename[100];


    cout << "Please enter the input file name: " << endl;
    cin >> infilename;

    fstream infile(infilename,ios::in);
    while(!infile)
    {
        cout<<"File could not be opened."<<endl;
        cout<<"Please enter the input file name:"<<endl;
        cin>>infilename;
        infile.open(infilename,ios::in);
    }
    infile>>garbage1>>garbage2;
    int i=0,j=0;
    while(infile>>giftnumber[i++]>>gifename[j++])
    {      }
    cout<<"Please choose a lucky number:"<<endl;
    cin>>lucky;

    while(lucky>i-1)
    {
        cout<<"Invalid input! Please enter again:"<<endl;
        cin>>lucky;
    }
     outfilename = infilename.substr(0,infilename.length()-4)+"out.txt";
    cout<<"Okay! Your Christmas present has been saved to "<<outfilename<<endl;
    fstream outfile(outfilename,ios::out);
    outfile<<"Congratulations! Your Christmas present is "<<gifename[lucky-1];
















    return 0;
}
