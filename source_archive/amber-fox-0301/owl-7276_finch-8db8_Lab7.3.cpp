#include <iostream>

using namespace std;


int number_of_addition=1,number_of_subtracttion=1;

void add(int &num)
{
    num+=number_of_addition;
    number_of_addition++;


}
void sub(int &num)
{
    num-=number_of_subtracttion;
   number_of_subtracttion++;

}
void factorization(int num)
{
   if(num<=0)cout<<"No factorization"<<endl<<endl;
   else
    {
    cout<<num<<" = ";
    for(int i=1;i<num;i++)
    {
        if(num%i==0)
            {
                cout<<i;
                cout<<",";
            }
    }
    cout<<num<<endl<<endl;


    }


}

int main()
{
    int number=0,choose,num_par=0;
    while(true){
        cout <<"The number now is "<<number<<endl;
        cout << "Choose a function:" << endl;
        cout << "1. Add    2. Sub    3. Factorization    4. Exit"<<endl<<endl;;
        cin>>choose;

        while(choose!=987)
        {
            switch (choose)
        {
            case 1:add(number);cout<<endl;break ;
            case 2:sub(number);cout<<endl;break ;
            case 3:factorization(number);break ;
            case 4:return 0;
            default:cout<<"Enter error!!"<<endl<<endl;choose=987;
        }
        break;
        }

    }

    return 0;
}

