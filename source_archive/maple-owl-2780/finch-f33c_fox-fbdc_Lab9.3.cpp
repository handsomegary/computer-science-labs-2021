#include <iostream>
#include<iomanip>
#include<cstring>
using namespace std;
void manr(int*);
void caer(int*);
void saas(int*);
void ssoacs(int*);
void menu(int*);
int main()
{
    int seats[15]={0};
    menu(seats);
    cout<<endl;
    cout<<"Thank you for using our system \nHave a nice day~~"<<endl;
    return 0;
}
void manr(int* seats){
    string a;
    cout<<endl;
    cout<<"***Make a new reservation***"<<endl;
    cout<<"Do you need a specified seat? (y/n) ";
    cin>>a;
    while(1){
        if(a=="y" or a=="n"){
            break;
        }
        else{
            cout<<"Invalid input, please enter your selection again: ";
            cin>>a;
        }

    }
    if(a=="y"){

        string sn;
        cout<<"Enter the seat number: ";
        cin>>sn;
        int isn;
        while(1){
            if(sn=="1" or sn=="2" or sn=="3" or sn=="4" or sn=="5" or sn=="6" or sn=="7" or sn=="8" or sn=="9" or sn=="10" or sn=="11" or sn=="12" or sn=="13" or sn=="14" or sn=="15"){

                isn=stoi(sn);
                break;
            }
            else{
                cout<<"Invalid input, please enter your selection again: ";
                cin>>sn;
            }
        }
        while(1){
            if(seats[isn-1]==0){
                cout<<"The seat number "<<sn<<" is reserved for you..."<<endl<<endl;
                seats[isn-1]++;
                break;
            }
            else{
                cout<<"The seat has been reserved, please enter your selection again: ";
                cin>>sn;

            }
        }
    }
    else{//a=='n'
        for(int i=0;i<15;i++){
            if(seats[i]==0){
                seats[i]++;
                cout<<"The seat number "<<i+1<<" is reserved for you..."<<endl<<endl;
                break;
            }


        }
    }


}
void caer(int* seats){
    int cancel;
    string snc;
    cout<<endl;
    cout<<"***Cancel an existing reservation***"<<endl;
    cout<<"Please enter the seat number which you want to cancel: ";
    cin>>snc;
    while(1){
            if(snc=="1" or snc=="2" or snc=="3" or snc=="4" or snc=="5" or snc=="6" or snc=="7" or snc=="8" or snc=="9" or snc=="10" or snc=="11" or snc=="12" or snc=="13" or snc=="14" or snc=="15"){

                cancel=stoi(snc);
                break;
            }
            else{
                cout<<"Invalid input, please enter your selection again: ";
                cin>>snc;
            }
        }
    if(seats[cancel-1]==0){
        cout<<"The seat is not reserved"<<endl<<endl;
    }
    else{
        cout<<"The seat number "<<cancel<<" is available now..."<<endl<<endl;
        seats[cancel-1]--;
    }



}
void saas(int* seats){
    cout<<endl;
    cout<<"***Show the all available seats***"<<endl;
    for(int i=0;i<15;i++){
        if(seats[i]==0){
            cout<<"seat "<<i+1<<endl;
        }

    }
    cout<<endl;
}
void ssoacs(int* seats){
    cout<<endl;
    cout<<"***Show the status of all seats***"<<endl;
    cout<<left<<setw(18)<<"Seat number"; cout<<"Status"<<endl;

    for(int i=0;i<15;i++){
        cout<<"Seat "<<left<<setw(13)<<i+1;
        if(seats[i]==0){
            cout<<"available"<<endl;
        }
        else
            cout<<"reserved"<<endl;


    }
    cout<<endl;
}
void menu(int* seats){

 string options;
    while(1){
        cout<<"*** Welcome to NCU theater reservation system ***"<<endl;
        cout<<"Please type 1 to make a new reservation"<<endl;
        cout<<"Please type 2 to cancel an existing reservation"<<endl;
        cout<<"Please type 3 to show the all available seats"<<endl;
        cout<<"Please type 4 to show the status of all current seats"<<endl;
        cout<<"Please type 5 to exit the system"<<endl;
        cout<<"Enter your selection Here: ";
        cin>>options;
        if(options=="5")
            return;;
        while(1){

            if(options=="1"){
                manr(seats);
                break;
            }
            else if(options=="2"){
                caer(seats);
                break;

            }
            else if(options=="3"){
                saas(seats);
                break;
            }
            else if(options=="4"){
                ssoacs(seats);
                break;
            }
            else if(options=="5")
                return;
            else{
                cout<<"Invalid input, please enter your selection again: ";
                cin>>options;
            }

        }
    }
}

