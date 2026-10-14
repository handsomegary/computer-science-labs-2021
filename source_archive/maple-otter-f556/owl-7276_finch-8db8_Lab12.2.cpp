#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    int luckynumber[52]={0},control=1,choose,d=0;
    string present[52];
    string infilename, outfilename;
    while(d==0)
    {
        cout << "Please enter the input file name:" << endl;
        cin>>infilename;
        ifstream ifile(infilename,ios::in);
        if(ifile.is_open())
        {
             while(!ifile.eof())
            {
                string a;
                ifile>>a;
                if(a=="Present")break;
            }
            while(!ifile.eof())
            {
            ifile>>luckynumber[control];
            ifile>>present[control];
            control++;
            }
            d=1;
        }
        else cout<<"File could not be opened."<<endl;
    }



    cout<<"Please choose a lucky number:"<<endl;
    cin>>choose;
   while(true)
   {
    if(choose>0&&choose<=control)break;
    else cout<<"Invalid input! Please enter again:"<<endl;
    cin>>choose;
   }
    outfilename = infilename.substr(0,infilename.length()-4)+"out.txt";
   ofstream ofile(outfilename,ios::out);
   ofile<<"Congratulations! Your Christmas present is "<<present[choose];
   cout<<"Okay! Your Christmas present has been saved to "<<outfilename;




    return 0;
}
