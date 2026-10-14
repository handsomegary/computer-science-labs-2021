#include <iostream>

using namespace std;
void find_mountain(int *const num, int *const Length);
int i=0; int first=0; int last;
int First;
int Last;
long long int n;
long long int a[50];
int main()
{
    int nu=0;int le=0;
    find_mountain(&nu,&le);
    cout<<nu<<endl;
    for(int i=First;i<=Last;i++){
        cout<<a[i]<<" ";
    }

    return 0;
}
void find_mountain(int *const num, int *const Length){
    while (cin >> n) {
        a[i] = n;

        if (cin.get() == '\n')
            break;

        i++;
    }

    int situation[50];//1 increase 0 decrease
    for(int j=0;j<=i;j++){
        if(a[j]<a[j+1]){
            situation[j+1]=1;
        }
        if(a[j]>a[j+1]){
            situation[j+1]=0;
        }
        if(a[j]==a[j+1]){
            situation[j+1]=situation[j];
        }


    }
    situation[0]=situation[1];

    for(int m=0;m<=i;m++){
        if(situation[m]==0 and m==i){
            last=m;
            if(last-first+1>*Length){
                *Length=last-first+1;
                First=first;
                Last=last;
            }
        }
        if(situation[m]==0 and situation[m+1]==1){
            last=m;
            if(last-first+1>*Length){
                *Length=last-first+1;
                First=first;
                Last=last;
            }

            first=m+1;
        }
        if(situation[m]==1 and situation[m+1]==0){
            *num+=1;
        }

    }
   // if(situation[])





}
