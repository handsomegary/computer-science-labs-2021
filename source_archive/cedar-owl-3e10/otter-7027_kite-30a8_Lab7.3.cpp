#include <iostream>

using namespace std;


int number_of_addition=1,number_of_subtracttion=1;

void add(int &number)//please complete the function
{
    number=number+number_of_addition;
    number_of_addition++;
}
void sub(int &number)//please complete the function
{
    number=number-number_of_subtracttion;
    number_of_subtracttion++;
}
void factorization(int number)//please complete the function
{
    if(number<=0)
        cout<<"No factorization"<<endl;

    else
    {
        cout<<number<<" = ";
        for(int i=1;i<=number;i++)
        {
            if(number%i==0&&i!=number)
                cout<<i<<",";
            else if(i==number)
                cout<<number<<endl;


        }

    }

}

int main()
{
    int number=0,choose;
    while(true)
    {
        cout <<"The number now is "<<number<<endl;
        cout << "Choose a function:" << endl;
        cout << "1. Add    2. Sub    3. Factorization    4. Exit"<<endl<<endl;;
        cin>>choose;
        if(choose>4||choose<0)
        {
            cout<<"Enter error!!"<<endl<<endl;
            continue;
        }
        if(choose==4)    break;
        switch(choose)
        {
            case 1:add(number);
                break;
            case 2:sub(number);
                break;
            case 3:factorization(number);
        }
        cout<<endl;

    }

    return 0;
}
