#include <iostream>

using namespace std;

int main()
{
    int row_a,column_a,row_b,column_b;
    int sum;
    cout << "Enter rows and columns for first matrix:" << endl;
    cin>>row_a>>column_a;
    cout<<"Enter rows and columns for second matrix:"<<endl;
    cin>>row_b>>column_b;
    if(column_a!=row_b)
    {
        cout<<"Cannot multiply these two matrixes.";
        return 0;
    }
    cout<<endl;
    long long int first[row_a][column_a];
    long long int second[row_b][column_b];
    long long int  ouput[row_a][column_b]={0};
    cout<<"Enter matrix 1:"<<endl;
    for(int i=0;i<row_a;i++)
        for(int j=0;j<column_a;j++)
        cin>>*(*(first+i)+j);
cout<<endl;
     cout<<"Enter matrix 2:"<<endl;
     for(int i=0;i<row_b;i++)
        for(int j=0;j<column_b;j++)
        cin>>*(*(second+i)+j);



cout<<endl;
      for(int i=0;i<row_a;i++)
      {
          for(int j=0;j<column_b;j++)
          {
              sum=0;
              for(int k=0;k<column_a;k++)
            {
                sum+=*(*(first+i)+k)  *   *(*(second+k)+j);
            }
            *(*(ouput+i)+j)=sum;
          }

      }



        cout<<"Output Matrix:"<<endl;
        for(int i=0;i<row_a;i++)
        {
            for(int j=0;j<column_b;j++)
            {
                cout<<*(*(ouput+i)+j)<<" ";
            }
            cout<<endl;

        }





    return 0;
}
