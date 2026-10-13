# 2024 Lab 4.3：Luggage Allocation：有限箱數精確分配

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

有有限數量的 1、5、10、25、50 公斤箱子。每種箱子可以不用，或使用不超過庫存的整數個；使用的每個箱子必須裝滿其容量。判斷選出的容量總和能否恰為目標重量 W，不要求輸出所選箱數。

## 輸入格式

依序輸入六個非負整數：W、1kg 箱數、5kg 箱數、10kg 箱數、25kg 箱數、50kg 箱數，以空白或換行分隔。

## 輸出格式

沒有提示。可精確分配印 `YES` 與換行，否則印 `NO` 與換行。任何負值或數值讀取失敗，在 stderr 印 `Enter a nonnegative weight and five nonnegative box counts.` 與換行，回傳 1。

## 限制與邊界

六個數值皆介於 0 與 9223372036854775807。W = 0 時選零個箱子即可，因此一定 YES。演算法時間不得隨各箱數增加而成五層窮舉；中間乘法須避免溢位。

## 解法說明

10、5、1 容量形成可整除鏈，對指定剩餘重量，可以優先用可用 10kg，再 5kg，最後檢查剩餘值是否 <= 1kg 庫存。50kg 與 25kg 合併為 25kg 單位 K = 2×50kg個數 + 25kg個數。

若沒有 25kg 箱，只能取偶數 K。只要有至少一個 25kg 箱，K 可連續取 0 到 2F+Q；為避免容量溢位，先將 F、Q 分別限制為不超過 W/50、W/25。剩餘重量對 10 的餘數只由 K 的奇偶決定。同一奇偶中使用最多單位會得到最小剩餘重量；減少兩單位只會增加 50kg，不會讓有限 10/5/1 箱更容易滿足。因此只檢查最大 K 與 K−1，時間、額外空間 O(1)。

單純全程先用大箱會漏解，例如 W=55，25kg 一個、10kg 三個可裝滿，即使也有一個 50kg 箱，也不應先鎖定它。

## 講義可確認的規則

Review 提供五種容量、有限箱數、精確分配目的，並以五層迴圈展示會逾時的窮舉，以及先觀察大箱的方向。

## 重建版自行補定的規則

輸入順序與 YES／NO 的格式、W=0、64 位數值範圍皆為重建補定。兩奇偶精確判斷是 repository 修訂解法，並非將 Review 的方向性貪婪提示當成完整正確演算法。

## 範例與說明

範例 1 選一個 25kg 與三個 10kg，恰為 55kg；50kg 箱可以不選。範例 2 只有一個 5kg 箱，無法裝滿 10kg。範例 3 確認 W=0 選零個箱子的邊界。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
55 0 0 3 1 1
```

### 範例 1 輸出

```text
YES
```

### 範例 2 輸入

```text
10 0 1 0 0 0
```

### 範例 2 輸出

```text
NO
```

### 範例 3 輸入

```text
0 0 0 0 0 0
```

### 範例 3 輸出

```text
YES
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
long long units = std::min(weight / 25, 2 * cappedFifties + cappedTwentyFives);
if (twentyFives == 0) {
    units -= units % 2;
    possible = smallerBoxesFit(weight - units * 25, ones, fives, tens);
} else {
    possible = smallerBoxesFit(weight - units * 25, ones, fives, tens);
    if (!possible && units > 0)
        possible = smallerBoxesFit(weight - (units - 1) * 25, ones, fives, tens);
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// Interface selected locally: weight, then counts of 1/5/10/25/50 kg boxes.
#include <algorithm>
#include <iostream>

bool smallerBoxesFit(long long weight, long long ones, long long fives, long long tens)
{
    weight -= std::min(tens, weight / 10) * 10;
    weight -= std::min(fives, weight / 5) * 5;
    return weight <= ones;
}

int main()
{
    long long weight = 0;
    long long ones = 0, fives = 0, tens = 0, twentyFives = 0, fifties = 0;
    if (!(std::cin >> weight >> ones >> fives >> tens >> twentyFives >> fifties)
        || weight < 0 || ones < 0 || fives < 0 || tens < 0 || twentyFives < 0 || fifties < 0) {
        std::cerr << "Enter a nonnegative weight and five nonnegative box counts.\n";
        return 1;
    }
    const long long cappedFifties = std::min(fifties, weight / 50);
    const long long cappedTwentyFives = std::min(twentyFives, weight / 25);
    long long units = std::min(weight / 25, 2 * cappedFifties + cappedTwentyFives);
    bool possible = false;
    if (twentyFives == 0) {
        units -= units % 2; // With only 50 kg boxes, 25 kg unit counts are even.
        possible = smallerBoxesFit(weight - units * 25, ones, fives, tens);
    } else {
        // 2*a+b spans every integer from 0 through 2*fifties+twentyFives.
        // For each parity, use its largest unit count. Smaller same-parity
        // counts add 50 kg to the remainder and cannot improve feasibility
        // for the divisible chain 10, 5, 1.
        possible = smallerBoxesFit(weight - units * 25, ones, fives, tens);
        if (!possible && units > 0) {
            possible = smallerBoxesFit(weight - (units - 1) * 25, ones, fives, tens);
        }
    }
    std::cout << (possible ? "YES\n" : "NO\n");
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab04` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab4_3.cpp -o lab4_3
./lab4_3
```

Windows PowerShell 執行 `./lab4_3.exe`。完整原始碼為 [`lab4_3.cpp`](../lab4_3.cpp)；機器可驗證範例在本目錄 `samples.json`。
