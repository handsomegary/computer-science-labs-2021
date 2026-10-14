#include <iostream>

using namespace std;

int main()
{
    long long int number;
    long long int year=0,month=0,day=0;
    int check,count_day=0;
    int february;
    cout<<"Enter a date (ex. 20211014): ";
    cin>>number;
    year=number/10000;
    month=(number%10000)/100;
    day=number%100;
    switch((year%4==0&&year%100!=0)||year%400==0)
    {
        case 1:february=29;       //true
            break;
        case 0:february=28;
    }

    switch(month)
    {
        case 1: check=31;
            break;
        case 2: check=february;
            break;
        case 3: check=31;
            break;
        case 4: check=30;
            break;
        case 5: check=31;
            break;
        case 6: check=30;
            break;
        case 7: check=31;
            break;
        case 8: check=31;
            break;
        case 9: check=30;
            break;
        case 10: check=31;
            break;
        case 11: check=30;
            break;
        case 12: check=31;
            break;
        default :check=0;
        }

    while(year<2021||month>12||day>check||month==0||day==0)
    {
        cout<<"This date does not exist or is within the calculation range.";
        cout<<" Please enter a correct date (ex. 20211014): ";
        cin>>number;
        year=number/10000;
        month=(number%10000)/100;
        day=number%100;
        switch((year%4==0&&year%100!=0)||year%400==0)
        {
            case 1:february=29;
                break;
            case 0:february=28;
        }
        switch(month)
        {
            case 1: check=31;
                break;
            case 2: check=february;
                break;

            case 3: check=31;
                break;
            case 4: check=30;
                break;
            case 5: check=31;
                break;
            case 6: check=30;
                break;
            case 7: check=31;
                break;
            case 8: check=31;
                break;
            case 9: check=30;
                break;
            case 10: check=31;
                break;
            case 11: check=30;
                break;
            case 12: check=31;
                break;
            default :check=0;
        }


    }
    long long int yy=2021,mm=1,dd=1;
    while(dd!=day||mm!=month||yy!=year)
    {
        switch((yy%4== 0&&yy%100!=0)||yy%400==0)
        {
            case 1:february=29;
                break;
            case 0:february=28;
        }


        while(mm<=12 && (dd!=day||mm!=month||yy!=year))
        {
            switch(mm)
            {
                case 1: check=31;
                    break;
                case 2: check=february;
                    break;
                case 3: check=31;
                    break;
                case 4: check=30;
                    break;
                case 5: check=31;
                    break;
                case 6: check=30;
                    break;
                case 7: check=31;
                    break;
                case 8: check=31;
                    break;
                case 9: check=30;
                    break;
                case 10: check=31;
                    break;
                case 11: check=30;
                    break;
                case 12: check=31;
                    break;
                default :check=0;
            }
             while( dd<=check && (dd!=day||mm!=month||yy!=year) )
            {
                dd++;
                count_day++;

            }
            while(dd>check)
            {
                dd=1;
                mm++;
            }

        }
        while( mm>12 )
        {
            yy++;
            mm=1;
        }


    }
    count_day=count_day%7;
    cout<<number<<" is ";
    switch(count_day)
    {
        case 0:cout<<"Friday.";
            break;
        case 1:cout<<"Saturday.";
            break;
        case 2:cout<<"Sunday.";
            break;
        case 3:cout<<"Monday ";
            break;
        case 4:cout<<"Tuesday.";
            break;
        case 5:cout<<"Wednesday.";
            break;
        case 6:cout<<"Thursday.";

    }
    return 0;

}
