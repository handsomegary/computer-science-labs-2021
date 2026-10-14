#include <iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<stdlib.h>
using namespace std;

int main()
{
    string l;
    string lot;string input;
    vector<string> a;

    while(1){
        cin>>lot;
        if(cin.get()=='\n')
            break;

    }


    while(1){
        cin>>input;
        a.push_back(input);
        if(cin.get()=='\n')
            break;
    }

    string match[6];
    cout<<endl;
    match[0]=lot.substr(5,3);//200
    match[1]=lot.substr(4,4);//1000
    match[2]=lot.substr(3,5);//4000
    match[3]=lot.substr(2,6);//10000
    match[4]=lot.substr(1,7);//40000
    match[5]=lot.substr(0,8);//200000
    int x=a.size();
    int n=5;int m=0;int store[a.size()];
    while(m<x){
        n=5;
        while(n>=0){
            if(a[m].find(match[n]) != string::npos){
                break;
            }
            else{
                n--;
            }
        }
        store[m]=n;
        m++;
    }
    m=0;
    int counter=0;

    while(m<x){

        if(store[m]<0)
            counter++;
        else{
            switch(store[m]){
            case 0:
                cout<<a[m]<<" won 2 hundred dollars!"<<endl;
                break;
            case 1:
                cout<<a[m]<<" won 1 thousand dollars!"<<endl;
                break;
            case 2:
                cout<<a[m]<<" won 4 thousand dollars!"<<endl;
                break;
            case 3:
                cout<<a[m]<<" won 10 thousand dollars!"<<endl;
                break;
            case 4:
                  cout<<a[m]<<" won 40 thousand dollars!"<<endl;
                  break;
            case 5:
                cout<<a[m]<<" won 200 thousand dollars!"<<endl;
                break;
            default:
                break;
            }

        }
        m++;
    }
    if(counter==x){
        cout<<"Won nothing. But, less is more.";
        return 0;
    }
    int get[6]={200,1000,4000,10000,40000,200000};
    int won=0;
    m=0;
    while(m<x){


            switch(store[m]){
            case 0:
                won+=get[0];
                break;
            case 1:
               won+=get[1];
                break;
            case 2:
                won+=get[2];
                break;
            case 3:
                won+=get[3];
                break;
            case 4:
                  won+=get[4];
                  break;
            case 5:
               won+=get[5];
                break;
            default:
                break;
            }

        m++;

    }
    cout<<"You totally won "<<won<<" dollars !!!";



    return 0;
}
