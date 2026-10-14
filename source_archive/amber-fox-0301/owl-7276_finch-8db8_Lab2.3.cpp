#include <iostream>

using namespace std;

int main()
{  float height,weight,bmi;

    cout << "Please enter your weight: " ;
    cin >>weight;
    cout <<"Please enter your height: ";
    cin>>height;
    bmi=weight/(height*height);
    cout<<"Your BMI is "<<bmi<< endl;
    if(bmi<=18.5)
       cout<<"You need to eat more"<<endl;
    else if(bmi< 24)
       cout<< "You are healthy"<<endl;
    else
       cout<< "You need to control your diet"<<endl;

    return 0;
}
