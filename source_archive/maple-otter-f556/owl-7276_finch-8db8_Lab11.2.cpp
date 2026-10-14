#include <iostream>

using namespace std;

void multilpate(int,int,int,int);
int aray[10][10]={0},bray[10][10]={0},result[10][10]={0};
int main()
{
    int aray_row=0,aray_colum=0,bray_row=0,bray_colum=0;
      int digita=1,digitb=1;
    cout << "Enter rows and columns for first matrix: "<<endl;
    cin>>aray_row>>aray_colum;
    cout << "Enter rows and columns for second matrix: "<<endl;
    cin>>bray_row>>bray_colum;
    if(aray_row!=bray_colum){cout<<"Cannot multiply these two matrixes.";return 0;}

    cout<<"\nEnter matrix 1: "<<endl;
       for(int j=1;j<=aray_row;j++)
    {
        for(int i=1;i<=aray_colum;i++)
        {
            cin>> *(*(aray+j)+i);
        }
    }
     cout<<"\nEnter matrix 2: "<<endl;
       for(int j=1;j<=bray_row;j++)
    {
        for(int i=1;i<=bray_colum;i++)
        {
            cin>> *(*(bray+j)+i);
        }
    }

    multilpate(aray_row,aray_colum,bray_row,bray_colum);
    cout<<"\nOutput Matrix:"<<endl;;
    for(int j=1;j<=aray_row;j++)
    {
        for(int i=1;i<=bray_colum;i++)
        {
            cout<< *(*(result+j)+i)<<" ";
        }
        cout<<endl;
    }
    return 0;
}
void multilpate(int aray_row,int aray_colum,int bray_row,int bray_colum)
{
    for(int j=1;j<=aray_row;j++)
    {
        for(int i=1;i<=bray_colum;i++)
        {
            int temp=0;
            for(int s=1;s<=aray_colum;s++)
            {
                temp+=*(*(aray+j)+s)*(*(*(bray+s)+i));
            }
            result[j][i]=temp;
        }
    }
}
