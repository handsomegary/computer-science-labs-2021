#include <iostream>
#include<string>
#include<vector>

using namespace std;
int count_value(string,int,int);
int small_count_value(string ,int,int);

int main()
{
    vector <int> index;
    vector <int> cal;  //1for+   2for-
    vector <int> value;
    int total=0,small_total=0;
    string input;
    cout<<"Please enter the arithmetic: ";
    cin>>input;
    index.push_back(-1);
    for(int i=0;i<input.length();i++)
    {
        if(input[i]=='+'||input[i]=='-')
        {
            index.push_back(i);
            if(input[i]=='+')
                cal.push_back(1);
            else if(input[i]=='-')
                cal.push_back(2);
        }
    }
    index.push_back(input.length());




    for(int i=0;i<index.size()-1;i++)
    {
        small_total=count_value(input,index[i],index[i+1]);
        value.push_back(small_total);
    }
    total=value[0];
    for(int i=0;i<cal.size();i++)
    {
        switch(cal[i])
        {
            case 1:total=total+value[i+1];
                break;
            case 2:total=total-value[i+1];
                break;

        }
    }
    cout<<total<<endl;


    return 0;
}
int count_value(string input,int low,int right)  //+ -
{
    int total=0;
    int small_total;
     vector <int> index;
     vector <int> value;
     vector <int> cal;     //   1 for *  2 for/    3for%
     index.push_back(low);
    for(int i=low+1;i<right;i++)
    {
        if(input[i]=='*'||input[i]=='/'||input[i]=='%')
        {
            index.push_back(i);
            if(input[i]=='*')
                cal.push_back(1);
            else if(input[i]=='/')
                cal.push_back(2);
            else
               cal.push_back(3);


        }
    }
    index.push_back(right);

    for(int i=0;i<index.size()-1;i++)
    {
        small_total=small_count_value(input,index[i],index[i+1]);
        value.push_back(small_total);
    }
    total=value[0];
    for(int i=0;i<cal.size();i++)
    {
        switch(cal[i])
        {
            case 1:total=total*value[i+1];
                break;
            case 2:total=total/value[i+1];
                break;
            case 3:total=total%value[i+1];
                break;
        }
    }
    return total;

}
int small_count_value(string input,int left,int right)
{
    int value=0;
    value=input[left+1]-'0';

    for(int i=left+2;i<right;i++)
    {
        value=value*10+input[i]-'0';
    }
    return value;
}

