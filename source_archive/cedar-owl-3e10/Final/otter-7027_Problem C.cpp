#include <iostream>
#include<vector>
#include<fstream>
using namespace std;

int main()
{
    int number;
    int total=0;
    string str;
    vector <int> stock;
    vector <int> index_low;
    vector <int> index_heigh;
    cout<<"File: ";
    getline(cin,str);
    fstream input(str,ios::in);
    input>>str>>str;

    while(input>>number)
    {
        stock.push_back(number);
        if(input.get()=='\n')
            break;
    }


    if(stock[0]<stock[1])
        index_low.push_back(0);

    for(int i=1; i<stock.size()-1; i++)
    {
        if(stock[i]<stock[i+1]&&stock[i]<stock[i-1])
        {
            index_low.push_back(i);
        }

    }



    for(int i=1; i<stock.size()-1; i++)
    {
        if(stock[i]>stock[i+1]&&stock[i]>stock[i-1])
            index_heigh.push_back(i);
    }
    if(stock[stock.size()-1]>stock[stock.size()-2])
    {
        index_heigh.push_back(stock.size()-1);
    }

    for(int i=0; i<index_heigh.size(); i++)
    {
        total+=stock[index_heigh[i]]-stock[index_low[i]];
    }
    cout<<"Maximum profit: "<<total<<endl;





    return 0;
}
