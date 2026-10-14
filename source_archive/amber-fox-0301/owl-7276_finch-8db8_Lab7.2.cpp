#include <iostream>
#include <cmath>

using namespace std;
int arry[4][10]={{0},{0},{0},{0}};
int digit[3]={0};
long long int paw (int a,int b  )
{
    if (b==0) return 1;
    else return a*paw(a,b-1);
}
void digitcheck(int ent,int digit2,int a)
{
    if(digit2>=0)
    {
        if (paw(10,digit2)<ent) digit[a]++;
        digitcheck(ent,digit2-1,a);
    }

}

void numbercheck (int ent,int digit,int a)
{
    if (digit>0)
    {
        int num=0;
        num=(ent%paw(10,digit)-ent%paw(10,digit-1))/paw(10,digit-1);
        arry[a][num]++;
        numbercheck (ent,digit-1,a);
    }
}
void printer(int target,int counter)
{
    if(counter>0)
    {
        cout<<target;
        printer(target,counter-1);
    }

}
int main()
{
    int ent1,ent2;
    cout << "Please enter two sequence numbers:" << endl;
    cin>>ent1;
    cin>>ent2;
    digitcheck(ent1,15,1);
    digitcheck(ent2,15,2);
    numbercheck(ent1,digit[1],1);
    numbercheck(ent2,digit[2],2);
    numbercheck(ent1,digit[1],3);
    numbercheck(ent2,digit[2],3);
    cout<<"Sorted result of the first sequence number: ";
    printer(0,arry[1][0]);
    printer(1,arry[1][1]);
    printer(2,arry[1][2]);
    printer(3,arry[1][3]);
    printer(4,arry[1][4]);
    printer(5,arry[1][5]);
    printer(6,arry[1][6]);
    printer(7,arry[1][7]);
    printer(8,arry[1][8]);
    printer(9,arry[1][9]);
    printer(10,arry[1][10]);
    cout<<endl;
    cout<<"Sorted result of the second sequence number: ";
    printer(0,arry[2][0]);
    printer(1,arry[2][1]);
    printer(2,arry[2][2]);
    printer(3,arry[2][3]);
    printer(4,arry[2][4]);
    printer(5,arry[2][5]);
    printer(6,arry[2][6]);
    printer(7,arry[2][7]);
    printer(8,arry[2][8]);
    printer(9,arry[2][9]);
    printer(10,arry[2][10]);
    cout<<endl;
    cout<<"Result: ";
    printer(10,arry[3][10]);
    printer(9,arry[3][9]);
    printer(8,arry[3][8]);
    printer(7,arry[3][7]);
    printer(6,arry[3][6]);
    printer(5,arry[3][5]);
    printer(4,arry[3][4]);
    printer(3,arry[3][3]);
    printer(2,arry[3][2]);
    printer(1,arry[3][1]);
    printer(0,arry[3][0]);
    return 0;
}
