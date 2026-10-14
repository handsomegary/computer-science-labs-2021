#include <iostream>
#include <iomanip>

using namespace std;

class matrixinform
{
public:
    int Adjmatr[6][6][6][6];
    int Deter;
    int Size;
    float contant[6][6];
};
int determin(matrixinform);
int func0();
int func1();
int func2(int);
int func3();


int main()
{
   int select=0;
   while(select!=5)
   {
      cout<<"---welcome to matrix calculation----"<<endl
   <<"0.notification"<<endl
   <<"1.find determine"<<endl
   <<"2.find nallity and rank"<<endl
   <<"3.matrix multiplication"<<endl
   <<"4.find basis of basic space"<<endl
   <<"5.find inverse matrix"<<endl
   <<"6.find eigenvalue"<<endl
   <<"7.exut"<<endl
   <<"Please enter your selection here:";
   cin>>select;


   switch(select)
   {
       case 0: func0();break;
       case 1: func1();break;
       case 2: func2(select);break;
       case 3: func3();break;
       case 4: func2(select);break;
       case 5:cout<<"Now developing";break;
       case 6:cout<<"Now developing";break;
       case 7:cout<<"BYE~~"<<endl;return 0;
       default:cout<<"illegal select"<<endl;

   }
   }

    return 0;
}
int func1()
{

   int siz=0;
    matrixinform matrix;
    cout<<endl<<"--- Now is selection 1---"<<endl;
    cout<<"please enter matrix size"<<endl;
    cin>>siz;
    cout<<"please enter matrix "<<endl;
    matrix.Size=siz;
    for(int i=1;i<=siz;i++)for(int j=1;j<=siz;j++)cin>>matrix.contant[i][j];
    cout<<"The determination of the matrix is "<<determin(matrix)<<endl;
}

int func2(int select)
{
    int row,colum,lank=0,enm=0;
    matrixinform rowvector[6],copi[6];
    int variable[6][6],nullbasis[6][6],freevarible;
    cout<<endl<<"---Now is selection "<<select<<"---"<<endl;
    cout<<"please enter row number: ";cin>>row;
    cout<<"please enter the column: ";cin>>colum;
    cout<<"please enter the matrix: "<<endl;
    for(int i=1;i<=row;i++)for(int j=1;j<=colum;j++){cin>>rowvector[i].contant[1][j];copi[i].contant[1][j]=rowvector[i].contant[1][j];}


    for(int i=1;i<row;i++)
    {
        enm=0;
        if(rowvector[i].contant[1][i]==0)
        {
            matrixinform temp;
            int check=i;
            while(rowvector[check].contant[1][i]==0)
            {
                check++;
                if(check==row){enm=1;break;}
            };
            rowvector[i]=temp;rowvector[i]=rowvector[check];rowvector[check]=temp;
        }
        if(enm==0)for(int j=i+1;j<=row;j++)
        {
            float o=(rowvector[j].contant[1][i]/rowvector[i].contant[1][i]);
            for(int k=1;k<=colum;k++)
            {
                rowvector[j].contant[1][k]-= o*rowvector[i].contant[1][k];
            }
        }
    }cout<<endl;
    for(int i=1;i<=row;i++)if(rowvector[i].contant[1][i]!=0)lank++;
    if(select==2)
    {
       for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=colum;j++)
        {
            cout<<setw(3)<<rowvector[i].contant[1][j]<<' ';
        }cout<<endl;
    }
    cout<<"the rank of the matrix is: "<<lank<<endl;
    if(row>colum)cout<<"the nullity of the matrix is: "<<colum-lank;
    else cout<<"the nullity of the matrix is: "<<row-lank;
    cout<<endl<<endl;
    }
    if(select==4)
    {
        cout<<"the basis of null space is"<<endl;
        /*for(int i=1;i<=freevarible;i++)
        {
            cout<<"[";
            for(int j=1;j<=row;j++)
            {
                cout<<setw(3)<<nullbasis[i][j]<<',';
            }cout<<"\b]"<<endl;
        }*/
        cout<<"the basis of row space is"<<endl;
            for(int i=1;i<=row;i++)
            {
                if(rowvector[i].contant[1][i]!=0)
                {
                    cout<<"[";
                    for(int j=1;j<=colum;j++){cout<<rowvector[i].contant[1][j]<<',';if(j==colum)cout<<"\b]";}
                }cout<<endl;
            }

        cout<<"the basis of column space is"<<endl;
        for(int i=1;i<=row;i++)
            {
                if(rowvector[i].contant[1][i]!=0)
                {
                    cout<<"[";
                    for(int j=1;j<=row;j++){cout<<copi[j].contant[1][i]<<',';if(j==row)cout<<"\b]";}
                }cout<<endl;
            }
    }

}


int func3()
{
     int colum[3],row[3],state=1;
     matrixinform matrix[3],result;
     cout<<endl<<"---Now is selection 3---"<<endl;
     cout<<"Please enter first matrix size"<<endl;
     cout<<"row: ";cin>>row[1];
     cout<<"column: ";cin>>colum[1];
     cout<<"Please enter first matrix "<<endl;
     for(int i=1;i<=row[1];i++)for(int j=1;j<=colum[1];j++)cin>>matrix[1].contant[i][j];
     while(state==1)
     {
        cout<<"Please enter second matrix size"<<endl;
     cout<<"row: ";cin>>row[2];
     cout<<"column: ";cin>>colum[2];
     if(colum[1]!=row[2])cout<<"The input is illegal,please enter again.";
     else state=0;
     }
     cout<<"Please enter second matrix"<<endl;
    for(int i=1;i<=row[2];i++)for(int j=1;j<=colum[2];j++)cin>>matrix[2].contant[i][j];
    for(int i=1;i<=row[1];i++)for(int j=1;j<=colum[2];j++){
        int temp=0;
        for(int k=1;k<=colum[1];k++)
        {
            temp+=matrix[1].contant[i][k]*matrix[2].contant[k][j];
        }
        result.contant[i][j]=temp;
    }
    cout<<"result:"<<endl;
    for(int i=1;i<=row[1];i++){{for(int j=1;j<=colum[2];j++)cout<<result.contant[i][j]<<' ';}cout<<endl;}
}


int determin(matrixinform matrix)
{
    float temp=0;matrixinform adj;
    if(matrix.Size==2)
    {
        return matrix.contant[1][1]*matrix.contant[2][2]-matrix.contant[1][2]*matrix.contant[2][1];
    }
    else
    {
    for(int i=1;i<=matrix.Size;i++)
    {
        for(int j=1;j<=matrix.Size;j++)
        {
            for(int k=2;k<=matrix.Size;k++)
            {
                adj.Size=matrix.Size-1;
                if(j<i)adj.contant[j][k-1]=matrix.contant[j][k];
                else if(j>i)adj.contant[j-1][k-1]=matrix.contant[j][k];
            }
        }
        if(i%2==1)temp+=matrix.contant[i][1]*determin(adj);
        else if(i%2==0)temp-=matrix.contant[i][1]*determin(adj);
    }
    return temp;
    }
}
func0()
{
    cout<<"////////////////caution///////////////////"<<endl
        <<"//                                      //"<<endl
        <<"// The calculator is only available for //"<<endl
        <<"// five by five matrix. More columns or //"<<endl
        <<"// rows will cause fatal compile error. //"<<endl
        <<"//                                      //"<<endl
        <<"//////////////////////////////////////////"<<endl;
}



