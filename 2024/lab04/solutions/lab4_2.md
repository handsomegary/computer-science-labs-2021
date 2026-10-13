# 2024 Lab 4.2：Company Investment Comparison：三家公司投資比較

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

先輸入 Andy、NCU、EE 三家公司的年利率。使用者可反覆選公司及每月投資金額，查看該公司十年的年底存款；每次查看都是一個從零開始的獨立方案。每年先投入十二個月的金額，再計算年利息。使用 while、continue、break 控制驗證及選單。

## 輸入格式

先輸入 Andy、NCU、EE 三個年利率。之後反覆輸入公司選項 C；C = 1、2、3 時再輸入每月投資金額 M，C = 4 時結束。所有數值以空白或換行分隔。

## 輸出格式

利率提示為 `Enter the annual interest rate for NAME company: `，NAME 依序 Andy、NCU、EE。非法利率印 `Out of range, interest rate should be in the range [0.00, 1.00]` 與換行，重印同一家提示。

每次選單先印一個換行，再印四行 `1. Andy company (P%)`、`2. NCU company (P%)`、`3. EE company (P%)`、`4. Exit this program`；P 為該公司年利率 × 100，固定兩位小數。再印不換行提示 `Please select a company (1-3) or enter 4 to exit: `。非法選項印 `Invalid selection.` 與換行並回選單。1–3 印 `Enter the monthly investment amount: `，接著印 `Year   Amount on deposit` 與換行，以及十列 setw(4) 年度、setw(21) 存款、兩位小數。每列加換行。

非法 M 印 `Invalid investment amount.` 與換行並回選單；4 不印告別詞。互動途中 EOF 正常回傳 0。計算溢位在 stderr 印 `Amount is outside the supported numeric range.` 與換行，回傳 1。

## 限制與邊界

三個利率皆為有限 double，0 <= r <= 1；M 為有限 double 且 M >= 0。每次方案 B0 = 0，By = (B(y−1)+12M)(1+r)，十個年度值須保持有限。非法文字輸入清除該行。

## 解法說明

readRate 的 while 以 continue 重試、break 接受。主選單 while 選取對應利率；每次設定 total = 0，使用十次 for 更新存款。每個合法方案固定十次運算，整體時間 O(選單操作次數)，額外空間 O(1)。

## 講義可確認的規則

Review 提供三家公司名稱、利率 0–1 的驗證字串、1–3 公司／4 結束、月投入 × 12 的 for 計算與十年畫面。

## 重建版自行補定的規則

每次計算從零開始、非負月投入、錯誤選項與金額訊息、4 不印告別詞，以及 EOF／數值溢位行為採上述介面。

## 範例與說明

三家公司利率 5%、4%、3%；選 Andy、每月投入 1000，相當每年投入 12000，第一年 12600.00、第十年 158481.45。第二次選單輸入 4 結束；利率 0 與 1 兩個邊界都合法。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
0.05 0.04 0.03
1
1000
4
```

### 範例 1 輸出

```text
Enter the annual interest rate for Andy company: Enter the annual interest rate for NCU company: Enter the annual interest rate for EE company: 
1. Andy company (5.00%)
2. NCU company (4.00%)
3. EE company (3.00%)
4. Exit this program
Please select a company (1-3) or enter 4 to exit: Enter the monthly investment amount: Year   Amount on deposit
   1             12600.00
   2             25830.00
   3             39721.50
   4             54307.58
   5             69622.95
   6             85704.10
   7            102589.31
   8            120318.77
   9            138934.71
  10            158481.45

1. Andy company (5.00%)
2. NCU company (4.00%)
3. EE company (3.00%)
4. Exit this program
Please select a company (1-3) or enter 4 to exit: 
```

此範例的標準輸出最後沒有換行；code fence 的結束行只用於排版。
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
double total = 0.0;
for (int year = 1; year <= 10; ++year) {
    total = (total + monthlyInvestment * 12) * (1.0 + rate);
    std::cout << std::setw(4) << year << std::setw(21) << total << '\n';
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

bool readRate(double& rate, const char* company)
{
    while (true) {
        std::cout << "Enter the annual interest rate for " << company << " company: ";
        if (!(std::cin >> rate)) {
            if (std::cin.eof()) {
                return false;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Out of range, interest rate should be in the range [0.00, 1.00]\n";
            continue;
        }
        if (!std::isfinite(rate) || rate < 0.0 || rate > 1.0) {
            std::cout << "Out of range, interest rate should be in the range [0.00, 1.00]\n";
            continue;
        }
        break;
    }
    return true;
}

int main()
{
    double rateAndy = 0.0;
    double rateNCU = 0.0;
    double rateEE = 0.0;
    if (!readRate(rateAndy, "Andy") || !readRate(rateNCU, "NCU") || !readRate(rateEE, "EE")) {
        return 0;
    }
    std::cout << std::fixed << std::setprecision(2);
    while (true) {
        std::cout << "\n1. Andy company (" << rateAndy * 100 << "%)\n"
                  << "2. NCU company (" << rateNCU * 100 << "%)\n"
                  << "3. EE company (" << rateEE * 100 << "%)\n"
                  << "4. Exit this program\n"
                  << "Please select a company (1-3) or enter 4 to exit: ";
        int company = 0;
        if (!(std::cin >> company)) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid selection.\n";
            continue;
        }
        if (company == 4) {
            break;
        }
        if (company < 1 || company > 3) {
            std::cout << "Invalid selection.\n";
            continue;
        }
        const double rate = company == 1 ? rateAndy : (company == 2 ? rateNCU : rateEE);
        double monthlyInvestment = 0.0;
        std::cout << "Enter the monthly investment amount: ";
        if (!(std::cin >> monthlyInvestment) || !std::isfinite(monthlyInvestment)
            || monthlyInvestment < 0.0) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid investment amount.\n";
            continue;
        }
        double total = 0.0;
        std::cout << "Year   Amount on deposit\n";
        for (int year = 1; year <= 10; ++year) {
            total = (total + monthlyInvestment * 12) * (1.0 + rate);
            if (!std::isfinite(total)) {
                std::cerr << "Amount is outside the supported numeric range.\n";
                return 1;
            }
            std::cout << std::setw(4) << year << std::setw(21) << total << '\n';
        }
    }
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab04` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab4_2.cpp -o lab4_2
./lab4_2
```

Windows PowerShell 執行 `./lab4_2.exe`。完整原始碼為 [`lab4_2.cpp`](../lab4_2.cpp)；機器可驗證範例在本目錄 `samples.json`。
