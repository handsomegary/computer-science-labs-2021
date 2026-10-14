#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    int a[100]={0},i=0,score=0, sum1=0;
    double sum = 0;
    cout << "Please enter the scores of all students: " << endl;
    while(cin>>score)
    {
        a[i]=score;sum += a[i];sum1 += a[i];
        if(cin.get()=='\n')break;
        i++;
    }
    if(sum1%(i+1) == 0) cout<<"avg = "<<fixed<<setprecision(0)<<sum/(i+1)<<endl;//µL²á·í¦³½ì
    else cout << "avg = " << fixed << setprecision(1) << sum/(i+1) <<  endl;
    for(int j = 0; j <= i; j++)
    {
        if(a[j] < 70)
        {
            cout<<"fail:"<<endl;
            break;
        }
    }
    for(int p = 0; p <= i; p++)
    {
        if(a[p] < 70)
        {
            cout<<p+1<<": "<<a[p]<< endl;
        }
    }
    return 0;
}
