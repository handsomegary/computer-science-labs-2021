#include <iostream>
#include<string>

using namespace std;

int main()
{
    string number;
    string input;
    getline(cin,input);
    number.assign(input,30,8);
    string check_number[10];
    int index=0;
    int    money[9]={0};
    while(1)
    {
        cin>>check_number[index++];
        if(getline()=='\n')
            break;
    }
    cout<<endl;
    for(int i=0;i<index;i++)
    {
        int index2=0;

        for(int j=0;number.length()-1-j!=-1;j++)
        {
            if(number[number.length()-1-j]==check_number[i][check_number[i].length()-1-j])
            {
                index2++;
            }
            else
            {
                break;
            }
        }
        switch(index2)
        {
        case 3:
            cout<<check_number[i]<<" won 2 hundred dollars!"<<endl;
            break;
        case 4:
            cout<<check_number[i]<<" won 1 thousand dollars!"<<endl;
            break;
        case 5:
            cout<<check_number[i]<<" won 4 thousand dollars!"<<endl;
            break;
        case 6:
            cout<<check_number[i]<<" won 10 thousand dollars!"<<endl;
            break;
        case 7:
            cout<<check_number[i]<<" won 40 thousand dollars!"<<endl;
            break;
        case 8:
            cout<<check_number[i]<<" won 200 thousand dollars!"<<endl;
            break;
        }
        money[index2]++;

    }
    int total_money=0;

    for(int i=3;i<=8;i++)
    {
        switch(i)
        {
        case 3:
            total_money+=money[i]*200;
            break;
        case 4:
            total_money+=money[i]*1000;
            break;
        case 5:
            total_money+=money[i]*4000;
            break;
        case 6:
            total_money+=money[i]*10000;
            break;
        case 7:
            total_money+=money[i]*40000;
            break;
        case 8:
            total_money+=money[i]*200000;
            break;
        }
    }
    if(total_money==0)
        cout<<"Won nothing. But, less is more."<<endl;
    else
        cout<<"You totally won "<<total_money<<" dollars !!!"<<endl;


    return 0;

}
