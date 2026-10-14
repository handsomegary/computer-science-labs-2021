#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
    cout << "Please enter the scores of all students:" << endl;
    vector <int> score;
    vector <int> index;
    double avg=0;
    int number;
    int a;
    while(1)
    {
        cin>>number;
        score.push_back(number);
        if(getchar()=='\n')
            break;
    }
    for(int i=0;i<score.size();i++)
    {
        avg+=score[i];
        if(score[i]<70)
            index.push_back(i+1);
    }
    avg=avg/score.size();
    a=avg*100;
    avg=(double)a/100;
    cout<<"avg = "<<avg<<endl;
    if(!index.empty())
    {
        cout<<"fail:"<<endl;
        for(auto n:index)
        {
            cout<<n<<": "<<score[n-1]<<endl;
        }



    }



    return 0;
}
