#include <iostream>
using namespace std;

int main()
{
    long int date = 0;
    long int days = 0;
    int months;
    int day;
    //label:
    cout << "Enter a date (ex. 20211014): ";
    cin >> date;
    months = date/100%100;
    day = date%100;
    while(date/10000%4!=0 && months==2 && day >= 29)
    {
    cout << "This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
    cin >> date;
    months = date/100%100;
    day = date%100;
    //cout << "a" << endl;
    }
    while(day > 31 || day == 0 || months == 0 || months > 12 || date < 20210101)
    {
    cout << "This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
    cin >> date;
    months = date/100%100;
    day = date%100;
    //cout << "b" << endl;
    }
    while(date%10000 == 230 || date%10000 == 231|| date%10000 == 431 || date%10000 == 631 || date%10000 == 931 || date%10000 == 1131)
    {
    cout << "This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
    cin >> date;
    months = date/100%100;
    day = date%100;
    //cout << "c" << endl;
    }
    //cout << months << endl;
    //cout << day << endl;
    if(date >= 20210101 && day > 0 && day <= 31 && months > 0 && months <= 12)
    {
    int leapyears = (date/10000 - 2020)/4;
    int commonyears = date/10000 - 2021 - leapyears;
    days = (commonyears - leapyears)*365 + leapyears*366;
    switch (months)
    {
    case 12:
        days += 30;
    case 11:
        days += 31;
    case 10:
        days += 30;
    case 9:
        days += 31;
    case 8:
        days += 31;
    case 7:
        days += 30;
    case 6:
        days += 31;
    case 5:
        days += 30;
    case 4:
        days += 31;
    case 3:
        days += 28;
    case 2:
        days += 31;
    case 1:
        days += 0;
    }
    days = days + day;
    int weekday = days % 7;
    switch (weekday)
    {
    case 1:
        cout << date << " is Friday.";
        break;
    case 2:
        cout << date << " is Saturday.";
        break;
    case 3:
        cout << date << " is Sunday.";
        break;
    case 4:
        cout << date << " is Monday.";
        break;
    case 5:
        cout << date << " is Tuesday.";
        break;
    case 6:
        cout << date << " is Wednesday.";
        break;
    default:
        cout << date << " is Thursday.";
        break;
    }
    }//cout << "\n";
    //goto label;
    return 0;
}
