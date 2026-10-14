#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string infilename, outfilename, gift[50];
    cout << "Please enter the input file name:" << endl;
    cin >> infilename;
    ifstream ifile(infilename,ios::in);
    while(!ifile)
    {
        cout << "File could not be opened." << endl << "Please enter the input file name:" << endl;
        cin >> infilename;
        ifile.open(infilename,ios::in);   //ifstream ifile(infilename, ios::in);
    }
    int luckynumber;
    string title1, title2;
    ifile >> title1 >> title2;
    int control = 1;
    while(!ifile.eof())
    {
        ifile >> luckynumber >> gift[control];
        control++;
    }
    int inputnumber;
    cout << "Please choose a lucky number:" << endl;
    cin >> inputnumber;
    while(inputnumber < 0 || inputnumber > luckynumber)
    {
        cout << "Invalid input! Please enter again:" << endl;
        cin >> inputnumber;
    }
    outfilename = infilename.substr(0,infilename.length()-4)+"out.txt";
    ofstream congrat (outfilename, ios::out);
    congrat << "Congratulations! Your Christmas present is " << gift[inputnumber];
    cout << "Okay! Your Christmas present has been saved to " << outfilename;
    return 0;
}
