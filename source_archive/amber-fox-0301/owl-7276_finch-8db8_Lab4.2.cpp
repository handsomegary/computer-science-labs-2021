#include <iostream>

using namespace std;






int main()
{
    long long int ymd,year=0,month=0,day=0,D=0,W=0;

    cout<<"Enter a date (ex. 20211014): ";

    while (cin>>ymd)
    {
       day=ymd%100;
        month=((ymd%10000)-(ymd%100))/100;
        year=ymd/10000;


    while (year%4!=0&&month==2&&day>=29)
       {
        cout<<"This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
        cin>>ymd;

       day=ymd%100;
        month=((ymd%10000)-(ymd%100))/100;
        year=ymd/10000;

       }


    if (month==4||month==6||month==9||month==11)
    {
         while(day>30)
     {
        cout<<"This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
        cin>>ymd;

       day=ymd%100;
        month=((ymd%10000)-(ymd%100))/100;
        year=ymd/10000;
     }
    }



     while(20210101>ymd||month>12||month<1||day>31||day<1)
     {
        cout<<"This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
        cin>>ymd;

       day=ymd%100;
        month=((ymd%10000)-(ymd%100))/100;
        year=ymd/10000;
     }





     switch(month)
    {
     case 12: D+=30;
     case 11: D+=31;
     case 10: D+=30;
     case 9: D+=31;
     case 8: D+=31;
     case 7: D+=30;
     case 6: D+=31;
     case 5: D+=30;
     case 4: D+=31;
     case 3:
     {
      if(year/4==0) D+=29;
      else D+=28;
     }
     case 2: D+=31;
    }

  W=(year-1)*365+((year-1)/4)+D+day-1;

  switch(W%7)
  {
  case 1:cout<<ymd<<" is Monday."; break;
  case 2:cout<<ymd<<" is Tuesday."; break;
  case 3:cout<<ymd<<" is Wednesday."; break;
  case 4:cout<<ymd<<" is Thursday."; break;
  case 5:cout<<ymd<<" is Friday." ; break;
  case 6:cout<<ymd<<" is Saturday." ;break;
  default :cout<<ymd<<" is Sunday." ; break;

  }return 0;
  }

  }






