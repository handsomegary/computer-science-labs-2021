//Lab2.3
#include <iostream>

using namespace std;

int main()
{
   double BMI,height,weight;   // declartion varible BMI,height,weight
   cout<<"Please enter your weight: ";
   cin>>weight;               //input weight
   cout<<"Please enter your height: ";
   cin>>height;               //input height
   BMI=weight/(height*height);  //calculate BMI
   cout<<"Your BMI is "<<BMI<<endl;
   if(BMI<18.5)                        //judge BMI
        cout<<"You need to eat more"<<endl;
   if(BMI>=18.5&&BMI< 24)
        cout<<"You are healthy"<<endl;
   if(BMI>=24)
        cout<<"You need to control your diet"<<endl;
   return 0;
}//end of main
