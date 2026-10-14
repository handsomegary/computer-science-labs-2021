#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
int a[11]={0,0,0,0,0,0,0,0,0,0,1};
int b[11]={0,0,0,0,0,0,0,0,0,0,1};
string s1;
string s2;
int tell=0;
// Sort a sequence number
long long int sort_a_sequence_number(long long int number,int x[],int c,int d){//d from 1
    if(number==0){
      if(tell==0){
        if(d==10){
            int ss1=stoi(s1);
            cout<<"Sorted result of the first sequence number: "<<ss1<<endl;
        }
        if(x[d]>0){
            if(x[d]-c==0)
                    return sort_a_sequence_number(number,x,0,d+1);
            switch(d){
            case 1:
                s1+="1";
                return sort_a_sequence_number(number,x,c+1,d);
            case 2:
                s1+="2";
                return sort_a_sequence_number(number,x,c+1,d);
            case 3:
                s1+="3";
                return sort_a_sequence_number(number,x,c+1,d);
            case 4:
                s1+="4";
                return sort_a_sequence_number(number,x,c+1,d);
            case 5:
                s1+="5";
                return sort_a_sequence_number(number,x,c+1,d);
            case 6:
                s1+="6";
                return sort_a_sequence_number(number,x,c+1,d);
            case 7:
                s1+="7";
                return sort_a_sequence_number(number,x,c+1,d);
            case 8:
                s1+="8";
                return sort_a_sequence_number(number,x,c+1,d);
            case 9:
                s1+="9";
                return sort_a_sequence_number(number,x,c+1,d);
            }
        }
        else{
            sort_a_sequence_number(number,x,0,d+1);
        }



    }

    if(tell==1){
        if(d==10){
            int ss2=stoi(s2);
            cout<<"Sorted result of the second sequence number: "<<ss2<<endl;
        }
        if(x[d]>0){
            if(x[d]-c==0)
                    return sort_a_sequence_number(number,x,0,d+1);
            switch(d){
            case 1:
                s2+="1";
                return sort_a_sequence_number(number,x,c+1,d);
            case 2:
                s2+="2";
                return sort_a_sequence_number(number,x,c+1,d);
            case 3:
                s2+="3";
                return sort_a_sequence_number(number,x,c+1,d);
            case 4:
                s2+="4";
                return sort_a_sequence_number(number,x,c+1,d);
            case 5:
                s2+="5";
                return sort_a_sequence_number(number,x,c+1,d);
            case 6:
                s2+="6";
                return sort_a_sequence_number(number,x,c+1,d);
            case 7:
                s2+="7";
                return sort_a_sequence_number(number,x,c+1,d);
            case 8:
                s2+="8";
                return sort_a_sequence_number(number,x,c+1,d);
            case 9:
                s2+="9";
                return sort_a_sequence_number(number,x,c+1,d);
            }
        }
        else{
            sort_a_sequence_number(number,x,0,d+1);
        }



    }






    }


    switch(number%10){

    case 1:
        x[1]++;
        return sort_a_sequence_number(number/10,x,c,d);
    case 2:
        x[2]++;
        return sort_a_sequence_number(number/10,x,c,d);
    case 3:
        x[3]++;
        return sort_a_sequence_number(number/10,x,c,d);
    case 4:
        x[4]++;
        return sort_a_sequence_number(number/10,x,c,d);
    case 5:
        x[5]++;
        return sort_a_sequence_number(number/10,x,c,d);
    case 6:
        x[6]++;
        return sort_a_sequence_number(number/10,x,c,d);
    case 7:
        x[7]++;
        return sort_a_sequence_number(number/10,x,c,d);
    case 8:
        x[8]++;
        return sort_a_sequence_number(number/10,x,c,d);
    case 9:
        x[9]++;
        return sort_a_sequence_number(number/10,x,c,d);
    }


    return 0;
}

// Divide a sequence number
long long int divide_a_sequence_number(long long int &number,int t,int q){
    if(q==5)
        return 0;
    if(t==0)
        number= stoi(s1);
    if(t==1)
        number= stoi(s2);

    return divide_a_sequence_number(number,t,q+1);
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
    cout << "Please enter two sequence numbers:" << endl;
    cin>>num1>>num2;
    sort_a_sequence_number(num1,a,0,1);
    tell++;
    sort_a_sequence_number(num2,b,0,1);
    divide_a_sequence_number(num1,0,0);
    divide_a_sequence_number(num2,1,0);
    cout<<"Result: ";
    combine(num1,num2);
    return 0;
}
