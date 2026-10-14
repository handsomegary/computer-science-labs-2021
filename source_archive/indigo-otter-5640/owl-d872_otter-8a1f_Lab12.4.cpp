#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int func(char arr[9][9],string target,int num,int m,int n)
{
    int length=target.length()-1;
    if(num>length)
        return 1;
    else if(target[num]==arr[m][n+1])
        return func(arr,target,num+1,m,n+1);
    else if(target[num]==arr[m][n-1])
        return func(arr,target,num+1,m,n-1);
    else if(target[num]==arr[m+1][n])
        return func(arr,target,num+1,m+1,n);
    else if(target[num]==arr[m-1][n])
        return func(arr,target,num+1,m-1,n);
    else
        return 0;

}
int main()
{
    char a[9][9];
    ifstream infile;
    infile.open("4_1.txt", ios::in);

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++){
            infile >> a[i][j];
        }

    string word;
    cin >> word;

    while(word!="-1")
    {
        int k=1,result=0;

        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(word[0]==a[i][j])
                    result = func(a,word,k,i,j);
                if(result == 1)
                    break;
            }
            if(result == 1)
                    break;
        }

        if(result == 1)
            cout << "True" << endl;
        else
            cout << "False" << endl;

        cin >> word;
    }

    return 0;
}
