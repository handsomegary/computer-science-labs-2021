#include <iostream>

using namespace std;

int main()
{
    cout << "-----Menu-----" << endl;
    int cold[9]={0,40,40,55,55,60,60,55,55};
    int coofe[9]={0,55,55,60,70,85,95,100,110};
    int hot[5]={0,85,100,100,100};
    int drink=1,favor,sum=0,money;
    while(drink!=0)
    {
        cin>>drink;
        if(drink==0)  break;
        cin>>favor;
        switch(drink)
        {
            case 1:money=cold[favor];
                break;
            case 2:money=coofe[favor];
                break;
            case 3:money=hot[favor];
                break;
        }
        sum+=money;
    }
    cout<<"Total Cost: "<<sum<<endl;


    return 0;
}
