#include <iostream>

using namespace std;

long long int a,year,month,day,sum;
int days[]={31,28,31,30,31,30,31,31,30,31,30,31};


 int put_a(){
    cin>>a;
    year=a/10000;
    month=(a/100)%100;
    day=a%100;
    switch(a<20210101){
        case 1:
            cout<<"This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
                    put_a();
        default:
            break;
    }
    switch(month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        case 4:
        case 6:
        case 9:
        case 11:
            switch(day>days[month] or day==0){
                case 1:
                    cout<<"This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
                    put_a();
                default:
                    break;
            }
            break;
        case 2:
            switch(year%4==0){
                case 1:
                    switch(day>29 or day==0){
                        case 1:
                            cout<<"This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
                            put_a();
                        default:
                            break;
                    }
                    break;

                default:
                    switch(day>28 or day==0){
                        case 1:
                            cout<<"This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
                            put_a();
                        default:
                            break;

                    }
			}
				break;

        default:
              cout<<"This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
              put_a();
              break;




    }

    return 0;
 }


int main()
{
    cout<<"Enter a date (ex. 20211014): ";

    put_a();


for(int i=2021;i<year;i++){  //¦~
    sum+=365;
    switch(i%4==0){
        case 1:
            sum++;
            break;
        default :
            break;
    }

}

for(int j=1;j<month;j++){
    sum+=days[j-1];
    switch(year%4==0){
        case 1:
            switch(j==2){
                case 1:
                    sum++;
                default:
                    break;
            }
        default:
           break;
    }

}
sum+=day;
sum--;

cout<<  a <<" is ";
switch(sum%7){
    case 0:
         cout<<"Friday.";
         break;
    case 1:
         cout<<"Saturday.";
         break;
    case 2:
         cout<<"Sunday.";
         break;
    case 3:
         cout<<"Monday.";
         break;
    case 4:
         cout<<"Tuesday.";
         break;
    case 5:
         cout<<"Wednesday.";
         break;
    case 6:
         cout<<"Thursday.";
         break;


}






}
