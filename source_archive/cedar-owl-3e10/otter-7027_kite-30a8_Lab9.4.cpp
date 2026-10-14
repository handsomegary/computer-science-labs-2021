#include <iostream>
#include<vector>
#include<iomanip>
using namespace std;
void spiral(int);

int main()
{
    int number;
    do
    {
        cout<<"Input dimension: ";
        cin>>number;
        if(number==-1) return 0;
        cout<<endl;
        spiral(number);
    }while(number!=-1);
   spiral(30);
    return 0;
}
void spiral(int size)
{
    char direction='r';
    int matrix[size][size];
    for(int i=0;i<size;i++)     //ªì©l¤Æ
        for(int j=0;j<size;j++)
            matrix[i][j]=0;
    int number=size*size;
    int row=0,column=0,rowbundary,columnbundary;
    for(int i=1;i<=number;i++)
    {
        matrix[row][column]=i;


        switch(direction)
        {
            case 'r':rowbundary=row;
                    columnbundary=column+1;
                break;
            case 'l':rowbundary=row;
                    columnbundary=column-1;
                break;
            case 'u':rowbundary=row-1;
                    columnbundary=column;
                break;
            case 'd':rowbundary=row+1;
                    columnbundary=column;

        }
        if((row==0&&column==size-1)||(row==size-1&&column==size-1)||(row==size&&column==0)||(matrix[rowbundary][columnbundary])!=0)
        {
            switch(direction)
            {
            case 'r':direction='d';
                break;
            case 'l':direction='u';
                break;
            case 'u':direction='r';
                break;
            case 'd':direction='l';
            }

        }
        switch(direction)
        {
            case 'r':column++;
                break;
            case 'l':column--;
                break;
            case 'u':row--;
                break;
            case 'd':row++;

        }



    }
    int width;
    if(number>=100)
    {
        width=3;
    }
    else if(number>=10)
    {
        width=2;
    }
    else
        width=1;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            cout<<setw(width)<<setfill('0')<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
cout<<endl;

}
