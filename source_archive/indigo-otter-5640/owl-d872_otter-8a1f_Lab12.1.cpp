#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int grade, n1 = 0, n2 = 0;
    string filetitle;
    cout << "Please enter the input file name:" << endl;
    cin >> filetitle;
    ifstream ifile(filetitle,ios::in);
    if(ifile.is_open());
    else
    {
        cout << "File could not be opened.";
        return 0;
    }
    while(!ifile.eof())
    {
        ifile >> grade;
        n1++;
        if(grade<60)
		{
			n2++;
		}
    }
    cout << n1 << endl << n2 << endl;

    return 0;
}
