#include <iomanip>
#include <iostream>
#include <limits>

int daysInMonth(long long year, int month)
{
    switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
    case 4: case 6: case 9: case 11: return 30;
    case 2: return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) ? 29 : 28;
    default: return 0;
    }
}

void addDays(long long& year, int& month, int& date, long long days)
{
    // A complete 400-year Gregorian cycle has the same date and weekday.
    year += 400 * (days / 146097);
    days %= 146097;
    while (days > 0) {
        const int remainingInMonth = daysInMonth(year, month) - date;
        if (days <= remainingInMonth) {
            date += static_cast<int>(days);
            break;
        }
        days -= remainingInMonth + 1;
        date = 1;
        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
}

int main()
{
    long long year = 0;
    int month = 0, date = 0, week = 0;
    std::cout << "Today: ";
    if (!(std::cin >> year >> month >> date >> week) || year < 1 || year > 2147483647LL
        || date < 1 || date > daysInMonth(year, month) || week < 1 || week > 7) {
        std::cerr << "Enter a valid Gregorian date and weekday from 1 (Mon.) to 7 (Sun.).\n";
        return 1;
    }
    int bottles = 0;
    std::cout << "How many bottles of the juice: ";
    if (!(std::cin >> bottles) || bottles < 1) {
        std::cerr << "The bottle count must be a positive integer.\n";
        return 1;
    }
    long long schedule = 0;
    int weeklyTotal = 0;
    bool valid = false;
    do {
        std::cout << "7-digit number: ";
        if (std::cin >> schedule) {
            valid = schedule >= 0 && schedule <= 9999999;
            long long digits = schedule;
            weeklyTotal = 0;
            for (int day = 0; day < 7; ++day) {
                const int quantity = static_cast<int>(digits % 10);
                if (quantity > 6) valid = false;
                weeklyTotal += quantity;
                digits /= 10;
            }
            if (weeklyTotal < 5) valid = false;
        } else {
            if (std::cin.eof()) return 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            valid = false;
        }
        if (!valid) std::cout << "Wrong 7-digit number entered. Please enter again!\n";
    } while (!valid);

    // Skip only complete weeks that leave at least one bottle unfinished.
    const long long wholeWeeks = (bottles - 1) / weeklyTotal;
    long long elapsed = wholeWeeks * 7;
    bottles -= static_cast<int>(wholeWeeks * weeklyTotal);
    while (bottles > 0) {
        int divisor = 1;
        for (int digit = week; digit < 7; ++digit) divisor *= 10;
        const int today = static_cast<int>(schedule / divisor % 10);
        bottles -= today; // Today's consumption happens before advancing a date.
        if (bottles > 0) {
            ++elapsed;
            week = week == 7 ? 1 : week + 1;
        }
    }
    addDays(year, month, date, elapsed);
    std::cout << "\nFinish all the juice on " << year << '/'
              << std::setfill('0') << std::setw(2) << month << '/'
              << std::setw(2) << date << std::setfill(' ');
    switch (week) {
    case 1: std::cout << " (Mon.).\n"; break;
    case 2: std::cout << " (Tue.).\n"; break;
    case 3: std::cout << " (Wed.).\n"; break;
    case 4: std::cout << " (Thu.).\n"; break;
    case 5: std::cout << " (Fri.).\n"; break;
    case 6: std::cout << " (Sat.).\n"; break;
    case 7: std::cout << " (Sun.).\n"; break;
    }
    return 0;
}
