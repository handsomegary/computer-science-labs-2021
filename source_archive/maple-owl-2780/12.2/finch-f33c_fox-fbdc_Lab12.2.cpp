#include <iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{

    string filename;
    string no,gift;int size=-1;


    while(1){
        cout<<"Please enter the input file name:"<<endl;
        cin>>filename;
        ifstream inFile(filename,ios::in);
        if(!inFile.is_open()){
            cout<<"File could not be opened."<<endl;
        }
        else
            break;
    }
    ifstream inFile(filename,ios::in);

    while( inFile >> no >> gift){

        size++;

    }
    string gift_list[size];
    inFile.seekg(0);int i=0;
    while(inFile>>no>>gift){
        gift_list[i]=gift;
        i++;
    }
    inFile.close();
    cout<<"Please choose a lucky number:"<<endl;
    int lucky_number;
    while(1){
        cin>>lucky_number;
        if(0>lucky_number or lucky_number>size)
            cout<<"Invalid input! Please enter again:"<<endl;
        else
            break;
    }
    ofstream outFile("2_1out.txt",ios::out);
    outFile<<"Congratulations! Your Christmas present is "<<gift_list[lucky_number];
    int lengh=filename.size();
    filename.insert(lengh-4,"out");
    cout<<"Okay! Your Christmas present has been saved to "<<filename;
    return 0;
}
