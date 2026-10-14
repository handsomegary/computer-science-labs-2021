#include <iostream>

using namespace std;

int main()
{   //block1: the following block is going to declare and initialize the variety
    int purchase,remain, hundread_r, fifty_r, ten_r,five_r, one_r,hundread_p,fifty_p,ten_p,five_p,one_p,purchase_t,purchase_t2;

         hundread_r=5;  hundread_p=0;
        fifty_r=5;     fifty_p=0;
        ten_r=5;       ten_p=0;
        five_r=5;      five_p=0;
        one_r=5;       one_p=0;

    string dop="0",YoN="0",strp="p",strd="d",strY="y",strN="n";
    cout << "*** Welcome to Quintuple Stimulus Vouchers System ***    " << endl;

    //block2: the following block is going to tell which types of vouchers and membership of NCU bank
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
        cout<< "Please enter the type of vouchers(d/p):  ";
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
            //block3: the following block is going to calculate the payment under the condition that the payment is clear

        purchase_t=purchase;

        if(purchase>hundread_r*100+fifty_r*50+ten_r*10+five_r*5+one_r*1)
            cout << "You don't have enough money.\n\n\n";
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

            //block4: this block is going to calculate the payment in the condition that the payment isn't clear
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


          //block5: the following block is going to output the result of the calculation
           if(100*hundread_r+50*fifty_r+10*ten_r+5*five_r+one_r==0)
            cout<<"You have no voucher remain bye~ "<<endl;
           else{

            if(purchase!=0)
            {
            cout <<"The payment is processed as follows:"<<endl;
            if(hundread_p>0)
            cout <<"    "<<hundread_p << " $100 vouchers "<<endl;
            if(fifty_p>0)
            cout <<"    "<<fifty_p <<" $50 voucher"<<endl;
            if(ten_p>0)
            cout <<"    "<<ten_p <<" $10 voucher"<<endl;
            if(five_p>0)
            cout <<"    "<<five_p <<" $5 voucher "<<endl;
            if(one_p>0)
            cout <<"    "<<one_p <<" $1 voucher "<<endl;
            }
            cout<<"the remaining vouchers are as follows"<<endl;
            if(hundread_r>0)
            cout <<"    "<<hundread_r<<" $100 vouchers "<<endl;
            if(fifty_r>0)
            cout<<"    "<<fifty_r<<" $50 vouchers"<<endl;
            if(ten_r>0)
            cout<<"    "<<ten_r<<" $10 vouchers"<<endl;
            if(five_r>0)
            cout<<"    "<<five_r<<" $5 vouchers"<<endl;
            if(one_r>0)
            cout<<"    "<<one_r<<" $1 vouchers"<<endl<<endl<<endl;

            hundread_p=0;
            fifty_p=0;
            ten_p=0;
            five_p=0;
            one_p=0;

           }

        }



}
}




