#include <iostream>

using namespace std;
int manr(int*);
int caer();
int saas();
int ssoacs();

int main()
{
    int seats[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int options;
    while(1){
        cout<<"*** Welcome to NCU theater reservation system ***"<<endl;
        cout<<"Please type 1 to make a new reservation"<<endl;
        cout<<"Please type 2 to cancel an existing reservation"<<endl;
        cout<<"Please type 3 to show the all available seats"<<endl;
        cout<<"Please type 4 to show the status of all current seats"<<endl;
        cout<<"Please type 5 to exit the system"<<endl;
        cout<<"Enter your selection Here: ";
        cin>>options;
        if(options==1)
            manr(seats);
        else if(options==2)
            caer();
        else if(options==3)
            saas();
        else if(options==4)
            ssoacs();
        else if(options==5)
            break;
        else
            cout<<"Invalid input, please enter your selection again: ";


    }
    cout<<"Thank you for using our system Have a nice day~~";
    return 0;
}
int manr(int* seats){
    char a;
    cout<<"***Make a new reservation***";
    cout<<"Do you need a specified seat? (y/n) ";
    a=cin.get();
    while(1){
        if(a!=121 or a!=110){
            cout<<"Invalid input, please enter your selection again: ";
            cin>>a;
        }
        else
            break;
    }
    if(a=='y'){
        int sn;
        cout<<"Enter the seat number: ";
        cin>>sn;
        while(sn<0 or sn>15){
            cout<<"Invalid input, please enter your selection again: ";
            cin>>sn;
        }
        while(1){
            if(seats[sn-1]==0){
                cout<<"The seat number "<<sn<<" is reserved for you...";
                seats[sn-1]++;
                break;
            }
            else{
                cout<<"The seat has been reserved, please enter your selection again: ";
                cin>>sn;
            }
        }
    }
    else{

    }


}
int caer(){

}
int saas(){

}
int ssoacs(){

}
