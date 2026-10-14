#include <iostream>
#include <fstream>
using namespace std;

ifstream infile;
ofstream outfile;

int main()
{
    string infilename, outfilename;

    cout << "Please enter the input file name: " << endl;
    cin >> infilename;
    outfilename = infilename.substr(0,infilename.length()-4)+"out.txt";

    return 0;
}

