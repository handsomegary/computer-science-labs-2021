#include <iostream>
#include<iomanip>
#include<cstring>
#include<iomanip>
#include<fstream>
using namespace std;
void manr(int*);
void caer(int*);
void saas(int*);
void ssoacs(int*);
void menu(int*);
void newmenu(int*,int);
void show_member();
void Member(int*);
void loadMember();
void changememberdata();
void findmemberdata();
struct memberdata{
    string username="";
    string password="";
    string phonenumber="";



}members[15];

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
        cout<<"Please type 6 to show member"<<endl;
        cout<<"Please type 7 to load member information"<<endl;
        cout<<"Please type 8 to change member data"<<endl;
        cout<<"Please type 9 to find member data"<<endl;
        cout<<"Please type 10 to exit the system"<<endl;
        cout<<"Enter your selection Here: ";
        cin>>options;
        if(options=="10")
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
            else if(options=="6"){
                show_member();
                break;
            }
            else if(options=="7"){
                loadMember();
                break;
            }
            else if(options=="8"){
                changememberdata();
                break;
            }
            else if(options=="9"){
                findmemberdata();
                break;
            }
            else if(options=="10")
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


    cout<<endl;

    string membership;
    cout<<"***NCU Theater Member Center***"<<endl;
    cout<<"Do you have the membership? (y/n) ";
    cin>>membership;
    while(1){
        if(!(membership=="y"||membership=="n")){
           cout<<"Invalid input, please enter your selection again: ";
           cin>>membership;

        }
        else
            break;
    }
    if(membership=="y"){
        int seeker;
        string u;
        string p;
        cout<<"Enter Username: ";
        cin>>u;
        cout<<"Enter Password: ";
        cin>>p;

        for(seeker=0;seeker<15;seeker++){
            if(u==members[seeker].username){

                if(p==members[seeker].password){
                    newmenu(s,seeker);
                    return;
                }


            }
        }
        if(seeker==15){
            cout<<"The username and the password don't match."<<endl;
        }


    }
    else if(membership=="n"){
        string su;string name;string word;string phonum;
        cout<<"Would you like to sign up? (y/n) ";
        cin>>su;
        while(1){
            if(!(su=="y"|| su=="n")){
                cout<<"Invalid input, please enter your selection again: ";
                cin>>su;

            }
            else
                break;
        }

        if(su=="y"){
            cout<<"Enter Username: ";
            cin>>name;
            members[hold].username=name;
            cout<<"Enter Password: ";
            cin>>word;
            members[hold].password=word;
            cout<<"Enter Phone number: ";
            cin>>phonum;
            members[hold].phonenumber=phonum;
            hold++;
            cout<<"Welcome! You are now a member of NCU theater."<<endl;
            cout<<"Please log in again."<<endl;
        }
        else if(su=="n"){
            cout<<"Okay! Have a nice day."<<endl;
        }



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
        cout<<"***Welcome back "<<members[who].username<<"***"<<endl;
        cout<<"Please type 1 to make a new reservation"<<endl;
        cout<<"Please type 2 to cancel an existing reservation"<<endl;
        cout<<"Please type 3 to show the all available seats"<<endl;
        cout<<"Please type 4 to show the status of all current seats"<<endl;
        cout<<"Please type 5 to log-out"<<endl;
        cout<<"Please type 6 to show member"<<endl;
        cout<<"Please type 7 to load member information"<<endl;
        cout<<"Please type 8 to change member data"<<endl;
        cout<<"Please type 9 to find member data"<<endl;
        cout<<"Please type 10 to exit the system"<<endl;
        cout<<"Enter your selection Here: ";
        cin>>options;
        if(options=="10"){
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
                loadMember();
                break;
            }
            else if(options=="5"){
                cout<<endl;
                return;
            }
            else if(options=="6"){
                show_member();
                break;
            }
            else if(options=="8"){
                changememberdata();
                break;
            }
            else if(options=="9"){
                findmemberdata();
                break;
            }
            else if(options=="10"){
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
void show_member(){
    cout<<endl;
    cout<<"***NCU Theater Membership***"<<endl;
    int counter=0;
    for(int i=0;i<15;i++){
        if(members[i].username=="")
            counter++;
    }
    if(counter==15){
        cout<<"No Member."<<endl;
    }
    else{
        cout<<"No.  Username"<<endl;
        for(int i=1;i<=15-counter;i++){
            if(i<=9)
                cout<<i<<"."<<"   "<<members[i-1].username<<endl;
            else
                cout<<i<<"."<<"  "<<members[i-1].username<<endl;
        }


    }
    cout<<endl;
}

void loadMember(){
    cout<<endl;
    cout<<"***Load member information***"<<endl;
    cout<<"Please enter the member file name: ";
    string filename;
    cin>>filename;
    ifstream loadFile(filename,ios::in);

    if(!loadFile.is_open()){
        cout<<"File could not be opened."<<endl<<endl;
        return;
    }
    string user_name,pass_word,phone_num;
    while(loadFile>>user_name>>pass_word>>phone_num){
        if(user_name=="Name")
            continue;
        if(pass_word=="Password")
            continue;
        if(phone_num=="Phone")
            continue;
        members[hold].username=user_name;
        members[hold].password=pass_word;
        members[hold].phonenumber=phone_num;
        hold++;
    }
    cout<<"The file "<<filename<<" has been loaded..."<<endl<<endl;


}
void changememberdata(){
    cout<<endl;
    cout<<"***Change member data***"<<endl;
    cout<<"Please type 1 to change password"<<endl;
    cout<<"Please type 2 to change phone number"<<endl;
    cout<<"Enter your selection Here: ";
    string selection;string un;string pawo;string newphonum;
    cin>>selection;
    while(1){
        if(selection=="1" or selection=="2"){
            cout<<"Enter Username: ";
            cin>>un;
            cout<<"Enter Password: ";
            cin>>pawo;
        int seeker;
        for(seeker=0;seeker<15;seeker++){
            if(un==members[seeker].username){

                if(pawo==members[seeker].password){
                    if(selection=="1"){
                        cout<<"Enter the new password: ";
                        string newpass;
                        cin>>newpass;
                        members[seeker].password=newpass;
                        cout<<endl;
                        return;

                    }
                    else{
                        cout<<"Enter the new phone number: ";
                        string newnum;
                        cin>>newnum;
                        members[seeker].phonenumber=newnum;
                        cout<<endl;
                        return;
                    }
                }


            }
        }
        if(seeker==15){
            cout<<"The username and the password don't match."<<endl;
            cout<<endl;
            return;
        }




        }
        else{
            cout<<"Invalid input, please enter your selection again: ";
            cin>>selection;
        }
    }


}
void findmemberdata(){
    cout<<endl;
    cout<<"***Find member data***"<<endl;
    cout<<"Please enter the search keyword: ";
    string keyword;int gotyou;int a[15]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    cin>>keyword;
    cout<<endl;
    cout<<"The searching keyword is \""<<keyword<<"\"..."<<endl;
    int finder=0;
    for(int i=0;i<15;i++){
        if(members[i].username=="" or keyword.length()>members[i].username.length()){

            continue;
        }
        for(int j=0;j<=members[i].username.length()-keyword.length();j++){
               for(int m=0;m<=members[i].username.length()-keyword.length();m++){
                    gotyou=0;
                    if(keyword[j]==members[i].username[m]){
                        for(int f=0;f<keyword.length();f++){
                            if(keyword[j+f]==members[i].username[m+f])
                                gotyou++;
                        }
                    }
                    if(gotyou==keyword.length()){
                        a[finder]=i;
                        finder++;
                    }
               }
        }

    }
    int tell=0;
    for(int i=0;i<15;i++){

        if(a[i]==-1){
            tell++;
        }
    }
    if(tell!=15){
        cout<<"The searching results are as follows:"<<endl;
        cout<<"*** Customer Information ***"<<endl;
        cout<<setw(11)<<left<<"Name";cout<<setw(15)<<left<<"Password";cout<<"Phone"<<endl;
        for(int i=0;i<15;i++){
            if(a[i]==-1)
                break;
            else{
                cout<<setw(11)<<members[a[i]].username<<setw(15)<<members[a[i]].password<<members[a[i]].phonenumber<<endl;
            }
        }



    }
    else{

        cout<<endl;
        cout<<"We cannot find the keyword."<<endl;

    }
    cout<<endl;
}
