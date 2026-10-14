#include <iostream>
#include<iomanip>
#include<cstring>

using namespace std;
void manr(int*);
void caer(int*);
void saas(int*);
void ssoacs(int*);
void menu(int*);
void newmenu(int*,int);
void Member(int*);
string username[15]={"!","!","!","!","!","!","!","!","!","!","!","!","!","!","!"};
string password[15]={"!","!","!","!","!","!","!","!","!","!","!","!","!","!","!"};
string options;
int hold=0;
int jumpout;


int main()
{
    int seats[15]={0};


    menu(seats);

    cout<<endl;
    cout<<"Thank you for using our system \nHave a nice day~~";
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
    if(jumpout==1){
        return;
     }
    while(1){
        if(jumpout==1)
            return;
        cout<<"*** Welcome to NCU theater reservation system ***"<<endl;
        cout<<"Please type 1 to make a new reservation"<<endl;
        cout<<"Please type 2 to cancel an existing reservation"<<endl;
        cout<<"Please type 3 to show the all available seats"<<endl;
        cout<<"Please type 4 to show the status of all current seats"<<endl;
        cout<<"Please type 5 to member center"<<endl;
        cout<<"Please type 6 to exit the system"<<endl;
        cout<<"Enter your selection Here: ";
        cin>>options;
        if(options=="6")
            return;
        while(1){
            if(jumpout==1){
                return;
            }
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
            else if(options=="5"){
                Member(seats);
                break;
            }
            else if(options=="6")
                return;
            else{
                cout<<"Invalid input, please enter your selection again: ";
                cin>>options;
            }

        }
    }
    if(jumpout==1){
        return;
     }
}
void Member(int* s){
    if(jumpout==1){
        return;
     }

    cout<<endl;

    string membership;
    cout<<"***NCU Theater Member Center***"<<endl;
    cout<<"Do you have the membership? (y/n) ";
    cin>>membership;
    if(membership=="y"){
        int seeker;
        string u;
        string p;
        cout<<"Enter Username: ";
        cin>>u;
        cout<<"Enter Password: ";
        cin>>p;

        for(seeker=0;seeker<15;seeker++){
            if(u==username[seeker]){

                if(p==password[seeker]){
                    newmenu(s,seeker);
                    return;
                }
                /*else{
                    cout<<"The username and the password don't match."<<endl;

                }*/

            }
        }
        if(seeker==15){
            cout<<"The username and the password don't match."<<endl;
        }


    }
    else if(membership=="n"){
        string su;string name;string word;
        cout<<"Would you like to sign up? (y/n) ";
        cin>>su;
        if(su=="y"){
            cout<<"Enter Username: ";
            cin>>name;
            username[hold]=name;
            cout<<"Enter Password: ";
            cin>>word;
            password[hold]=word;
            hold++;
            cout<<"Welcome! You are now a member of NCU theater."<<endl;
            cout<<"Please log in again."<<endl;
        }
        else if(su=="n"){
            cout<<"Okay! Have a nice day."<<endl;
        }
        else{
             cout<<"Invalid input, please enter your selection again:";
        }


    }
    else{
        cout<<"Invalid input, please enter your selection again:";

    }
    if(jumpout==1){
        return;
     }
    cout<<endl;
}
void newmenu(int* seats,int who){
    cout<<endl;
    if(jumpout==1){
        return;
     }

    while(1){
        cout<<"*** Welcome to NCU theater reservation system ***"<<endl;
        cout<<"***Welcome back "<<username[who]<<"***"<<endl;
        cout<<"Please type 1 to make a new reservation"<<endl;
        cout<<"Please type 2 to cancel an existing reservation"<<endl;
        cout<<"Please type 3 to show the all available seats"<<endl;
        cout<<"Please type 4 to show the status of all current seats"<<endl;
        cout<<"Please type 6 to exit the system"<<endl;
        cout<<"Please type 7 to log-out"<<endl;
        cout<<"Enter your selection Here: ";
        cin>>options;
        if(options=="6"){
            jumpout=1;
            return;
        }
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
            else if(options=="7"){
                cout<<endl;
                return;
            }
            else if(options=="6"){
                jumpout=1;
                return;
            }
            else{
                cout<<"Invalid input, please enter your selection again: ";
                cin>>options;
            }

        }

    }



}
