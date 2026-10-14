#include <iostream>

using namespace std;

int main()
{
    long long int date;

    cout << "Enter a date (ex. 20211014): ";
    while (cin >> date
    
    {
        long long int year = date / 10000;
        int month = date % 10000 / 100;
        int days = date % 100;
        switch (year >= 2021)
        {
        case 1:
            break;
        default:
            cout << "This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
            continue;
        }
        switch (month <= 12 && month >= 1)
        {
        case 1:
            break;
        default:
            cout << "This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
            continue;
        }

        switch (month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            switch (days > 31 || days == 0)
            {
            case 1:
                cout << "This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
                continue;
            default:
                break;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            switch (days > 30 || days == 0)
            {
            case 1:
                cout << "This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
                continue;
            default:
                break;
            }
            break;
        case 2:
            switch (year % 4 == 0)
            {
            case 1:
                switch (days > 29 || days == 0)
                {
                case 1:
                    cout << "This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
                    continue;
                default:
                    break;
                }
                break;
            default:
                switch (days > 28 || days == 0)
                {
                case 1:
                    cout << "This date does not exist or is within the calculation range. Please enter a correct date (ex. 20211014): ";
                    continue;
                default:
                    break;
                }
                break;
            }
            break;
        }
        int day = 5;
        for (long long int y = 2022; y <= year; y++)
        {
            day++;
            switch (y % 4)
            {
            case 1:
                day++;
                break;
            default:
                break;
            }
            while (day >= 7)
                day -= 7;
        }
        day--; // 更正1/1號星期幾
        switch (year % 4)
        {
        case 0:
            switch (month)
            {
            case 1:
                break;
            case 2:
                day += 31;
                break;
            case 3:
                day += 60;
                break;
            case 4:
                day += 91;
                break;
            case 5:
                day += 121;
                break;
            case 6:
                day += 152;
                break;
            case 7:
                day += 182;
                break;
            case 8:
                day += 213;
                break;
            case 9:
                day += 244;
                break;
            case 10:
                day += 274;
                break;
            case 11:
                day += 305;
                break;
            case 12:
                day += 335;
                break;
            }
            break;
        default:
            switch (month)
            {
            case 1:
                break;
            case 2:
                day += 31;
                break;
            case 3:
                day += 59;
                break;
            case 4:
                day += 90;
                break;
            case 5:
                day += 120;
                break;
            case 6:
                day += 151;
                break;
            case 7:
                day += 181;
                break;
            case 8:
                day += 212;
                break;
            case 9:
                day += 243;
                break;
            case 10:
                day += 273;
                break;
            case 11:
                day += 304;
                break;
            case 12:
                day += 334;
                break;
            }
            break;
        }
        days += day;
        days %= 7;
        switch (days)
        {
        case 1:
            cout << date << " is Monday.\n";
            break;
        case 2:
            cout << date << " is Tuesday.\n";
            break;
        case 3:
            cout << date << " is Wednesday.\n";
            break;
        case 4:
            cout << date << " is Thursday.\n";
            break;
        case 5:
            cout << date << " is Friday.\n";
            break;
        case 6:
            cout << date << " is Saturday.\n";
            break;
        case 0:
            cout << date << " is Sunday.\n";
            break;
        }
        break;
    }
    return 0;
}
