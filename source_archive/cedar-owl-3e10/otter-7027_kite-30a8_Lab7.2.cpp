#include <iostream>

using namespace std;

// Sort a sequence number
long long int divide(long long int num)
{

    return (num%10);
}
long long int sort_number(long long int num)
{

    if(num>=100)
    {
        if(divide(num)<divide(num/10))
        {
            return sort_number(100*(num/100)+10*divide(num)+divide(num/10));

        }
        else
            return (10*sort_number(num/10)+divide(num));
    }
    else if(divide(num)<divide(num/10))
            return (10*divide(num)+divide(num/10));
    else return num;

}
long long int sort_sort(long long int num,long long int d)
{

    if(d!=0)
    return sort_sort(sort_number(num),d/10);
    else return sort_number(num);
}

// Divide a sequence number



// Merge two sequence numbers
void combine(long long int num1,long long int num2){

    if(num1%10>num2%10){
        cout<<num1%10;
        combine(num1/10,num2);
    }
    else if(num1%10<num2%10){
        cout<<num2%10;
        combine(num1,num2/10);
    }
    else if(num1%10==num2%10 && num1%10!=0 && num2%10!=0){
        cout<<num1%10;
        cout<<num2%10;
        combine(num1/10,num2/10);
    }
    else{
        return ;
    }

}



int main()
{
    long long int num1,num2;
    cout << "Please enter two sequence numbers:" << endl;
    cin>>num1>>num2;
    num1=sort_sort(num1,num1);
    num2=sort_sort(num2,num2);
    cout<<"Sorted result of the first sequence number: "<<num1<<endl;
    cout<<"Sorted result of the second sequence number: "<<num2<<endl;
    cout<<"Result: ";
    combine(num1,num2);
    cout<<endl;

    return 0;
}
