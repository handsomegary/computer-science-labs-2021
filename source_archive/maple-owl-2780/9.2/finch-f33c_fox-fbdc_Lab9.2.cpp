#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int s;
    cout << "Enter a number:" << endl;
    cin>>s;
    vector<int> v(s);
    for(int i=0;i<s;i++){
        cin>>v[i];
    }
    int i, j, tmp;

    for(i = s-1; i > 0; i--)
    {
        for(j = 0; j <= i-1; j++)
        {
            if( v[j] > v[j+1])
            {
                tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }

    cout<<"After sorting:"<<endl;
    for(int i=0;i<s;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    cout<<"Median value of this series is: ";
    int m;
    if(s%2==0){

       m=v[s/2-1]+v[s/2];
       m/=2;
       cout<<m;
    }
    else{
        m=v[s/2];
        cout<<m;
    }



    return 0;
}
