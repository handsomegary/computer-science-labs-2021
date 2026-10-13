# 2024 Lab 5.3：Debugging：果汁喝完的日期

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

修正果汁日期程式：輸入今天的年月日與星期，以及瓶數與一週每天的飲用數量。從今天開始先喝今天規定的量；如果仍有果汁才前進一天。求全部喝完的公曆日期與星期。今天可喝超過剩餘瓶數，當日即喝完。

## 輸入格式

依序為四個整數 Y、M、D、W；W=1表示週一，...，7表示週日。接著輸入瓶數 B，再輸入一個非負整數 S。S左側補零到七位，從左到右對應週一至週日每日瓶數。S中每位為0–6，七位和至少5；不符則重新輸入S。例0512002表示週一0、週二5、週三1、週四2、週五0、週六0、週日2。

## 輸出格式

依序印不換行的 `Today: `、`How many bottles of the juice: `、`7-digit number: `。S非法印 `Wrong 7-digit number entered. Please enter again!` 與換行，重印S提示。完成後先印一個換行，再印 `Finish all the juice on Y/MM/DD (DAY.).` 與換行；月日各兩位，不足補0，年數不補零。DAY依序Mon、Tue、Wed、Thu、Fri、Sat、Sun，實際格式例如`(Thu.).`。

日期／星期不合法，stderr印 `Enter a valid Gregorian date and weekday from 1 (Mon.) to 7 (Sun.).` 與換行並回傳1。瓶數不合法，stderr印 `The bottle count must be a positive integer.` 與換行並回傳1。讀S時文字失敗清除該行；EOF正常結束。

## 限制與邊界

1 <= Y <= 2147483647，M、D必須構成有效公曆日期；1 <= W <= 7；1 <= B <= 2147483647；0 <= S <= 9999999且滿足上述逐位限制。W以使用者給定的參考星期為準，不要求與實際日曆星期一致。前導零不影響S數值，512002與0512002等價。完成日期可能跨過輸入年份上界，年數以long long輸出。

## 解法說明

先每次重試重設驗證旗標與weeklyTotal。今日先扣瓶數，避免多算一天。為效率先略過 (B−1)/weeklyTotal 個完整星期，保證略過後至少留一瓶；再逐日處理剩餘一週以內的部分，得到elapsed。公曆加天使用每月天數與400年146097天週期跳過，含正確閏世紀。星期更新採用switch各case都有break。固定七位解析、最多七日處理和剩餘400年內月份處理，時間與瓶數無線性關係，額外空間O(1)。

## 講義可確認的規則

Review P113019 的圖碼可確認輸入順序、週一=1、七位每位<=6且總和>=5、錯輸S訊息、今日先扣、結果前換行、switch缺break修正，以及2024/09/03週二47瓶0512002應在2024/10/03週四完成。

## 重建版自行補定的規則

完整除錯源碼未提供，依圖碼重建其可見行為；本題現明確採用上述日期驗證、瓶數／年份範圍、數值補足七位及使用者參考星期。完整星期與400年跳過是repository修訂演算法。

## 範例與說明

範例1為Review指出的日期修正：2024/09/03週二47瓶，週飲量10，喝完日為10/03週四。範例2只有1瓶，週二可喝5瓶，所以今天就喝完，沒有推進日期。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
2024 9 3 2
47
0512002
```

### 範例 1 輸出

```text
Today: How many bottles of the juice: 7-digit number: 
Finish all the juice on 2024/10/03 (Thu.).
```

### 範例 2 輸入

```text
2024 9 3 2
1
0512002
```

### 範例 2 輸出

```text
Today: How many bottles of the juice: 7-digit number: 
Finish all the juice on 2024/09/03 (Tue.).
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
const long long wholeWeeks = (bottles - 1) / weeklyTotal;
long long elapsed = wholeWeeks * 7;
bottles -= static_cast<int>(wholeWeeks * weeklyTotal);
while (bottles > 0) {
    int divisor = 1;
    for (int digit = week; digit < 7; ++digit) divisor *= 10;
    const int today = static_cast<int>(schedule / divisor % 10);
    bottles -= today; // 先喝今天的量。
    if (bottles > 0) {
        ++elapsed;
        week = week == 7 ? 1 : week + 1;
    }
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
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
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab05` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab5_3.cpp -o lab5_3
./lab5_3
```

Windows PowerShell 執行 `./lab5_3.exe`。完整原始碼為 [`lab5_3.cpp`](../lab5_3.cpp)；機器可驗證範例在本目錄 `samples.json`。
