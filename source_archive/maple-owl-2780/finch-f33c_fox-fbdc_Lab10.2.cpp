#include <iostream>
#include <vector>
using namespace std;
void find_mountain(int *const num, int *const Length);
int m=0;
int l=0;
long long int n;
long long int a[50];
int b[50]={0};
int first;int First;
int last;int Last;
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
    int c=0;
    while (cin >> n) {
        a[m] = n;

        if (cin.get() == '\n')
            break;

        m++;
    }
    if(a[0]<a[1]){
        b[0]=-1;
    }
    if(a[m]<a[m-1]){
        b[m]=-1;
    }
    for(int i=1;i<m;i++){
        if(a[i-1]<a[i] && a[i]>a[i+1]){
            *num+=1;
            b[i]=1;
        }
        if(a[i-1]>a[i] && a[i]<a[i+1]){
            b[i]=-1;
        }

    }

    for(int i=0;i<=m;i++){
        if(b[i]==-1 and c==0){
            c=1;
            first=i;
            continue;
        }
        if(c==1 and b[i]==-1)
            c++;
        if(c==2){
            c=1;
            last=i;
            if((last-first+1)>*Length){
                *Length=(last-first+1);
                Last=last;
                First=first;
            }
            first=last;
        }

    }


}






