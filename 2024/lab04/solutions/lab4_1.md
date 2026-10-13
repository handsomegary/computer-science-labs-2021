# 2024 Lab 4.1：Annual Interest Calculator：十年定期儲蓄

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

每年年初投入相同金額 A，當年度年底以年利率 r 計息。初始存款為 0，輸出第 1–10 年年底存款。當年度投入的金額也會取得當年度利息。使用 for、setw、fixed、setprecision。

## 輸入格式

依序輸入年度投入金額 A 與小數形式年利率 r。例如 0.05 表示 5%。兩個數值以空白或換行分隔。

## 輸出格式

依序印 `Enter the annual investment amount: ` 與 `Enter the annual interest rate (as a decimal, e.g., 0.05 for 5%): `，提示均沒有換行。再印 `Year   Amount on deposit` 與換行。每列用 setw(4) 印年度、setw(21) 印存款，右對齊、空格補足欄寬，存款固定兩位小數；每列最後換行。setw 是最小欄寬，較長值不截斷。

A 不合法時 stderr 印 `Invalid investment amount.`；r 不合法印 `Invalid interest rate.`；計算中超出有限數值範圍印 `Amount is outside the supported numeric range.`。錯誤訊息皆加換行，回傳 1。

## 限制與邊界

A、r 都是 double 可表示的有限非負數，沒有 r <= 1 的額外限制。十年每個年底結果均須保持為有限 double，否則依錯誤規則結束。內部不逐年取整到分，僅輸出時顯示兩位小數。

## 解法說明

令 B0 = 0，每年計算 By = (B(y−1) + A) × (1+r)。Review 修正片段的關鍵是先加上當年的 annualInvestment，再乘利率；省略年年投入就會算成另一種存款。固定十次迴圈，時間與額外空間 O(1)。

## 講義可確認的規則

Review 明確給定十年、先投入再計息的修正版 for 片段、兩個輸入提示、setw(4)／setw(21) 及兩位小數畫面，1000／0.05 的十年表格亦可確認。

## 重建版自行補定的規則

初始存款 0，金額及利率採有限非負 double；沒有利率上限；溢位錯誤、欄位標題與換行依上述精確介面。這是重建版接受的正式規格。

## 範例與說明

年度投入 1000、利率 5%，第一年 (0+1000)×1.05 = 1050，第十年顯示 13206.79。若 A = 0，各年度結果都是 0.00；若 r = 0，年底存款恰為年度 × A。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
1000 0.05
```

### 範例 1 輸出

```text
Enter the annual investment amount: Enter the annual interest rate (as a decimal, e.g., 0.05 for 5%): Year   Amount on deposit
   1              1050.00
   2              2152.50
   3              3310.12
   4              4525.63
   5              5801.91
   6              7142.01
   7              8549.11
   8             10026.56
   9             11577.89
  10             13206.79
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
for (int year = 1; year <= 10; ++year) {
    totalAmount = (totalAmount + annualInvestment) * (1.0 + annualRate);
    std::cout << std::setw(4) << year << std::setw(21)
              << std::fixed << std::setprecision(2) << totalAmount << '\n';
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
#include <cmath>
#include <iomanip>
#include <iostream>

int main()
{
    double annualInvestment = 0.0;
    double annualRate = 0.0;
    std::cout << "Enter the annual investment amount: ";
    if (!(std::cin >> annualInvestment) || !std::isfinite(annualInvestment)
        || annualInvestment < 0.0) {
        std::cerr << "Invalid investment amount.\n";
        return 1;
    }
    std::cout << "Enter the annual interest rate (as a decimal, e.g., 0.05 for 5%): ";
    if (!(std::cin >> annualRate) || !std::isfinite(annualRate) || annualRate < 0.0) {
        std::cerr << "Invalid interest rate.\n";
        return 1;
    }
    double totalAmount = 0.0;
    std::cout << "Year   Amount on deposit\n" << std::fixed << std::setprecision(2);
    for (int year = 1; year <= 10; ++year) {
        totalAmount = (totalAmount + annualInvestment) * (1.0 + annualRate);
        if (!std::isfinite(totalAmount)) {
            std::cerr << "Amount is outside the supported numeric range.\n";
            return 1;
        }
        std::cout << std::setw(4) << year << std::setw(21) << totalAmount << '\n';
    }
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab04` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab4_1.cpp -o lab4_1
./lab4_1
```

Windows PowerShell 執行 `./lab4_1.exe`。完整原始碼為 [`lab4_1.cpp`](../lab4_1.cpp)；機器可驗證範例在本目錄 `samples.json`。
