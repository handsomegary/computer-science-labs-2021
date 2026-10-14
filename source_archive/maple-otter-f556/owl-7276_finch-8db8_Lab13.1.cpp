#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    string l,m,n,o,p;
    string enter[20],compare,enter2[20];
    int digit=1,langh;
    cin>>l>>m>>n>>o>>p;
    cin>>compare;
    langh=compare.length();
    //cout<<langh<<endl;
    //cout<<compare[1];
    while(true)
    {
        enter2[digit]=enter[digit];
        cin>>enter[digit];
        digit++;
        char ch=getchar();
        if(ch=='\n')break;
    }

    int number[20]={0},total=0;
    for(int i=1;i<digit;i++)
    {
       int con=0;
       while(true)
       {
           //cout<<compare[langh-con-2]<<" "<<enter[i][langh-con-2]<<endl;
           if(compare[langh-con-2]==enter[i][langh-con-2]){number[i]++;con++;}
           else break;
       }
    }

        cout<<endl;

        for(int i=1;i<digit;i++)
        {
            string message;
            switch(number[i])
            {
                case 3:message="2 hundred";number[i]=200;break;
                case 4:message="1 thousand";number[i]=1000;break;
                case 5:message="4 thousand";number[i]=4000;break;
                case 6:message="10 thousand";number[i]=10000;break;
                case 7:message="40 thousand";number[i]=40000;break;
                case 8:message="200 thousand";number[i]=200000;break;
                default:number[i]=0;
            }
            if(number[i]>2)cout<<enter[i]<<" won "<<message<<" dollars!"<<endl;

        }
        for(int i=1;i<digit;i++)total+=number[i];
        if(total!=0)cout<<"You totally won "<<total<<" dollars !!!"<<endl;
        else cout<<"Won nothing. But, less is more."<<endl;

    return 0;
}
