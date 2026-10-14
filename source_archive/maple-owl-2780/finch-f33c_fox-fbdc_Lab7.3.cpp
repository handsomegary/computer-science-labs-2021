#include <iostream>

using namespace std;


int number_of_addition=1,number_of_subtracttion=1;

void add(int &a){
    //please complete the function
    a+=number_of_addition;
    number_of_addition++;
}
void sub(int &b){
    //please complete the function
    b-=number_of_subtracttion;
    number_of_subtracttion++;
}
void factorization(int c,int d){
    //please complete the function
    if(c>0)
    {
            if(d==1)
                cout<<c<<" = ";
            if(d<=c){

                if(c%d==0 and d>1)
                {
                    cout<<",";
                }

                if (c%d==0)
                {
                    cout<<d;
                }
                if(c==d)
                    cout<<endl;
                factorization(c,d+1);

            }
       /*for(int x=1;x<=c;x++)
        {
            if(c%x==0 and x>1)
            {
            cout<<",";
            }

            if (c%x==0)
            {
                cout<<x;
            }

      }
      */
    }
      else
      {
           cout<<"No factorization"<<endl;
      }






}

int main()
{
    int number=0,choose;
    while(true){
        cout <<"The number now is "<<number<<endl;
        cout << "Choose a function: " << endl;
        cout << "1. Add    2. Sub    3. Factorization    4. Exit"<<endl<<endl;;
        cin>>choose;
        if(!(choose==1 or choose==2 or choose==3 or choose==4))
            cout<<"Enter error!!"<<endl<<endl;
        if(choose==1)
            add(number);
        else if(choose==2)
            sub(number);
        else if(choose==3)
            factorization(number,1);
        else if(choose==4)
            break;
        cout<<endl;
    }

    return 0;
}

