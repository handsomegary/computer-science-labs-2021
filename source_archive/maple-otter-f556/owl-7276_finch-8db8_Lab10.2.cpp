#include <iostream>
#include <iomanip>
using namespace std;

void find_mountain(int*const ,int *const,int[]);
void compare(int []);
int bray[100]={0};
int c=1;
int start=0;
int cont=0;
int mux=0;
int main()
{
  int aray[101]={0},digit=1,num=0,length=0;
  while(true)
    {
        cin>>aray[digit];
        digit++;
        char ch=getchar();
        if(ch=='\n')break;
    }
    find_mountain(&num,&length,aray);
   cout<<cont<<endl;

    compare(aray);



    for(int i=0;i<=mux;i++)
    {
        cout<<aray[start+i]<<" ";
    }

    return 0;
}

void find_mountain(int *const num,int *const length,int aray[100])
{

        for(int i=0;i<=10;i++)
{
    bray[i]=1;
}

    for(int i=2;i<=98;i++)
    {
        if(aray[i-1]<aray[i]&&aray[i]>=aray[i+1])
          {
              cont++;
          }
         if(aray[i-1]>aray[i]&&aray[i]<aray[i+1])
          {
              bray[c]=i;c++;
          }
          if(aray[i+2]==0&&aray[i+1]==0&&aray[i]>aray[i-1])cont--;
    }
}
void compare(int aray[100])
{


        for(int i=0;i<=100;i++)
    {
        if((bray[i+1]-bray[i])>mux)
        {
        mux=bray[i+1]-bray[i];
        start=bray[i];
        }
    }


}
