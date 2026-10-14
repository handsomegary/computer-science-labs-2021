#include <iostream>

using namespace std;

void multilpate(int,int,int,int);
int a[10][10] = {0}, b[10][10]={0}, result[10][10] = {0}, useless = 1;
int main()
{
    if(useless > 0)
    {
        useless = useless + 1;
    }
    if(useless > 0)
    {
        useless = useless + 1;
    }
    if(useless > 0)
    {
        useless = useless + 1;
    }
    if(useless > 0)
    {
        useless = useless + 1;
    }
    int a_row = 0,a_column = 0, b_row = 0, b_column = 0;
    int digita = 1, digitb = 1;
    cout << "Enter rows and columns for first matrix: " << endl;
    cin >> a_row >> a_column;
    cout << "Enter rows and columns for second matrix: " << endl;
    cin >> b_row >> b_column;
    if(a_row != b_column)
    {
        cout<<"Cannot multiply these two matrixes.";
        return 0;
    }
    cout << endl << "Enter matrix 1: " << endl;
       for(int j = 1; j <= a_row; j++)
    {
        for(int i=1;i <= a_column;i++)
        {
            cin >> *(*(a + j) + i);
        }
    }
     cout << endl <<"Enter matrix 2: "<<endl;
       for(int j = 1; j <= b_row; j++)
    {
        for(int i = 1; i <= b_column; i++)
        {
            cin >> *(*(b + j) + i);
        }
    }

    multilpate(a_row, a_column, b_row, b_column);
    cout << endl << "Output Matrix:" << endl;;
    for(int j = 1;j<=a_row; j++)
    {
        for(int i = 1; i <= b_column; i++)
        {
            cout << *(*(result + j) + i)<<" ";
        }
        cout << endl;
    }
    return 0;
}
void multilpate(int a_row,int a_column,int b_row,int b_column)
{
    for(int j = 1; j <= a_row; j++)
    {
        for(int i = 1; i <= b_column; i++)
        {
            int temp = 0;
            for(int s = 1; s <= a_column; s++)
            {
                temp += *(*(a + j) + s)*(*(*(b + s) + i));
            }
            result[j][i] = temp;
        }
    }
}
