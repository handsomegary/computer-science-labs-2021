#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int grade,number1=0,number2=0;
    string filetiltal,a;
    cout << "Please enter the input file name:" << endl;
    cin>>filetiltal;
    ifstream ifile(filetiltal,ios::in);
    if(ifile.is_open());
    else {cout<<"File could not be opened."; return 0;}
    while(!ifile.eof())
    {
        ifile>>grade;
        number1++;
        if(grade<60)number2++;
    }
    cout<<number1<<endl<<number2<<endl;

    return 0;
}
