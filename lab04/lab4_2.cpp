#include <iostream>
#include <limits>

// The Gregorian leap-year rule is calendar validation, not a weekday formula.
bool isLeapYear(long long year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int daysInMonth(long long year, int month)
{
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        switch (isLeapYear(year)) {
        case true: return 29;
        default: return 28;
        }
    default:
        return 0;
    }
}

int main()
{
    long long date = 0;
    long long year = 0;
    int month = 0;
    int day = 0;
    bool valid = false;
    std::cout << "Enter a date (ex. 20211014): ";
    while (!valid) {
        switch (static_cast<bool>(std::cin >> date)) {
        case true:
            year = date / 10000;
            month = static_cast<int>(date / 100 % 100);
            day = static_cast<int>(date % 100);
            valid = date >= 20210101 && day >= 1
                    && day <= daysInMonth(year, month);
            break;
        default:
            switch (std::cin.eof()) {
            case true: return 0;
            default: break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        switch (valid) {
        case false:
            std::cout << "This date does not exist or is within the calculation range. "
                         "Please enter a correct date (ex. 20211014): ";
            break;
        default: break;
        }
    }

    // Every 400 Gregorian years contain 146097 days, exactly 20871 weeks.
    // Omit whole identical cycles, then accumulate each remaining year/month.
    // This uses the calendar and the stated 2021-01-01 Friday reference.
    const long long yearsToCount = (year - 2021) % 400;
    int elapsedDays = 0;
    long long currentYear = 2021;
    while (currentYear < 2021 + yearsToCount) {
        switch (isLeapYear(currentYear)) {
        case true: elapsedDays += 366; break;
        default: elapsedDays += 365; break;
        }
        ++currentYear;
    }
    int currentMonth = 1;
    while (currentMonth < month) {
        elapsedDays += daysInMonth(year, currentMonth);
        ++currentMonth;
    }
    elapsedDays += day - 1;
    std::cout << date << " is ";
    switch (elapsedDays % 7) {
    case 0: std::cout << "Friday"; break;
    case 1: std::cout << "Saturday"; break;
    case 2: std::cout << "Sunday"; break;
    case 3: std::cout << "Monday"; break;
    case 4: std::cout << "Tuesday"; break;
    case 5: std::cout << "Wednesday"; break;
    case 6: std::cout << "Thursday"; break;
    }
    std::cout << ".\n";
    return 0;
}
