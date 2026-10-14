#include <iostream>

using namespace std;

int main()
{   int purchase,remain, hundread_r, fifty_r, ten_r,five_r, one_r,hundread_p,fifty_p,ten_p,five_p,one_p,purchase_t,purchase_t2;

         hundread_r=5;  hundread_p=0;
        fifty_r=5;     fifty_p=0;
        ten_r=5;       ten_p=0;
        five_r=5;      five_p=0;
        one_r=5;       one_p=0;

    string dop="0",YoN="0",strp="p",strd="d",strY="y",strN="n";


    cout << "*** Welcome to Quintuple Stimulus Vouchers System ***    " << endl;



while(hundread_r*100+fifty_r*50+ten_r*10+five_r*5+one_r*1>0)
{
        cout<< "Plaese eneter the good price: ";
        cin >> purchase;
        if(purchase<0)
        {
            cout<<"bye~";
            break;
        }
        dop="0";
        YoN="0";
    while(dop!=strd&&dop!=strp)
        {
        cout<< "Please enter the type of voucher(d/p):  ";
        cin>> dop;
        if(dop!=strd&&dop!=strp)
        cout<<"try again"<<endl;
        }
        if (dop==strd)
        {
        while(YoN!=strY&&YoN!=strN)
            {
            cout<< "Are you a member of NCU bank(y/n): ";
            cin>> YoN;
            if(YoN!=strY&&YoN!=strN)
            cout<<"try again"<<endl;
            }
            if(YoN==strY)
            purchase=purchase*0.72;

            else purchase=purchase*0.8;

        }
        else purchase=purchase*0.9;


         cout<<"The price you need to pay: "<< purchase <<endl;
            //the following block is going to calculate the payment under the condition that the payment is clear

        purchase_t=purchase;

        if(purchase>hundread_r*100+fifty_r*50+ten_r*10+five_r*5+one_r*1)
            cout << "you don't have enough money.\n";
        else{

            while(purchase>=hundread_p*100+100)
            {
            if(hundread_p>=hundread_r)
                break;
             purchase_t=purchase_t-100;
             hundread_p=hundread_p+1;

            }
            purchase_t2=purchase_t;
            while(purchase_t2>=fifty_p*50+50)
            {
                if(fifty_p>=fifty_r)
                    break;
                purchase_t=purchase_t-50;
                fifty_p=fifty_p+1;

            }
            purchase_t2=purchase_t;
            while(purchase_t2>=ten_p*10+10)
            {
                 if(ten_p>=ten_r)
                    break;
                purchase_t=purchase_t-10;
                ten_p=ten_p+1;

            }
            purchase_t2=purchase_t;
             while(purchase_t2>=five_p*5+5)
            {
                if(five_p>=five_r)
                    break;
                purchase_t=purchase_t-5;
                five_p=five_p+1;

            }

            one_p=purchase_t;

            //this block is going to calculate the payment in the condition that the payment isn't clear
        if (one_p>one_r)
        {
               hundread_p=0;fifty_p=0;ten_p=0;five_p=0;one_p=0;//to initialize the payment

               while(purchase>0)
             {
                if(hundread_p==hundread_r)
                    break;
                purchase=purchase-100;
                hundread_p=hundread_p+1;
             }
             while(purchase>0)
             {
                if(fifty_r==0)
                    break;
                purchase=purchase-50;
                fifty_p=fifty_p+1;
             }
             while(purchase>0)
             {
                 if(ten_r==0)
                    break;
                 purchase=purchase-10;
                 ten_p=ten_p+1;
             }
            while(purchase>0)
            {
                if(five_r==0)
                    break;
                purchase=purchase-5;
                five_r+1;
            }
            while(purchase>0)
            {
                purchase=purchase-1;
                one_r+1;
            }
        }
            hundread_r=hundread_r-hundread_p;
            fifty_r=fifty_r-fifty_p;
            ten_r=ten_r-ten_p;
            five_r=five_r-five_p;
            one_r=one_r-one_p;


           if(100*hundread_r+50*fifty_r+10*ten_r+5*five_r+one_r==0)
            cout<<"you have no voucher remain bye~ "<<endl;
           else{

            if(purchase!=0)
            {
            cout <<"the payment is"<<endl;
            if(hundread_p>0)
            cout <<"100$ is "<<hundread_p<<endl;
            if(fifty_p>0)
            cout<<"50$ is "<<fifty_p<<endl;
            if(ten_p>0)
            cout<<"10$ is "<<ten_p<<endl;
            if(five_p>0)
            cout<<"5$ is "<<five_p<<endl;
            if(one_p>0)
            cout<<"1$ is "<<one_p<<endl;
            }
            cout<<"the remain is"<<endl;
            if(hundread_r>0)
            cout <<"100$ is "<<hundread_r<<endl;
            if(fifty_r>0)
            cout<<"50$ is "<<fifty_r<<endl;
            if(ten_r>0)
            cout<<"10$ is "<<ten_r<<endl;
            if(five_r>0)
            cout<<"5$ is "<<five_r<<endl;
            if(one_r>0)
            cout<<"1$ is "<<one_r<<endl;

            hundread_p=0;
            fifty_p=0;
            ten_p=0;
            five_p=0;
            one_p=0;

           }

        }



}
}




