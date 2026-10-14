#include <iostream>

using namespace std;

// Sort a sequence number
long long int sort_a_sequence_number(){

    return 0;
}

// Divide a sequence number
long long int divide_a_sequence_number(){

    return 0;
}


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
    cout << "Please enter two sequence:" << endl;
    cin>>num1>>num2;

    return 0;
}
