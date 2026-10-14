#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double avg=0,sum=0,check=0;
    int aray[200]={0};
    int digit=1;
    int inset=0;
    cout << "Please enter the scores of all students:" << endl;
     while(true)
    {
        cin>>aray[digit];
        if(aray[digit]<70)check=1;
        digit++;
        char ch=getchar();
        if(ch=='\n')break;
    }

    for(int i=1;i<=digit;i++)
    {
       sum+=aray[i];
    }
    avg=sum/(digit-1);
    cout<<"avg = "<<setprecision(2)<<avg<<endl;
    if(check==1){
        cout<<"fail:"<<endl;
        for(int i=1;i<=3;i++){
            if (aray[i]<70) cout<<i<<": "<<aray[i]<<endl;
        }

    }

    return 0;
}

