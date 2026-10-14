#include <iostream>

using namespace std;

int main()
{
    int a[4][8]={{0,0,0,0},
                 {40,40,55,55,60,60,55,55},
                 {55,55,60,70,85,95,100,110},
                 {85,100,100,100}};

   /* cout<<"Cold Drink"<<endl;
    cout<<"1. Coca Cola 40"<<endl;
    cout<<"2. Coca Cola Zero 40"<<endl;
    cout<<"3. Lemon Tea 55"<<endl;
    cout<<"4. Green Tea 55"<<endl;
    cout<<"5. Black Tea 60"<<endl;
    cout<<"6. Milk Tea 60"<<endl;
    cout<<"7. Apple Juice 55"<<endl;
    cout<<"8. Berry Juice 55"<<endl;
    cout<<"Coffee"<<endl;
    cout<<"1. Espresso 55"<<endl;
    cout<<"2. Hot Americano 55"<<endl;
    cout<<"3. Iced Anericano 60"<<endl;
    cout<<"4. Hot Latte 70"<<endl;
    cout<<"5. Iced Latte 85"<<endl;
    cout<<"6. Toffee Latte 95"<<endl;
    cout<<"7. Rose Latte 100"<<endl;
    cout<<"8. Iced Rose Latte 110"<<endl;
    cout<<"Hot Drink"<<endl;
    cout<<"1. Hot Chocolate 85"<<endl;
    cout<<"2. Chocolate Milk 100"<<endl;
    cout<<"3. Matcha Milk 100"<<endl;
    cout<<"4. Rose Woolong 100"<<endl;
    */
    cout<<"-----Menu-----"<<endl;
    int sum=0;
    while(1){
        int m,b;
        cin>>m;
        if(m==0)
            break;
        cin>>b;
        if(b==0)
            break;
        sum+=a[m][b-1];


    }
    cout<<"Total cost: "<<sum;







    return 0;
}
