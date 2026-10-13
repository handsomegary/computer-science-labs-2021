# 2024 Lab 5.2：Combination：吃完餅乾的全部組合

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

Joe 每天只能從三個不同數量中選一個數量吃餅乾。請列出恰好吃完 N 個餅乾的所有組合，不列相同天數組合的不同日期排列。每個組合中依每天數量小到大表示；各組合先依最小數量的天數升冪，再依總天數升冪。用 do/while 驗證數量，用 for 找出解。

## 輸入格式

先輸入非負整數 N；其後輸入三個數量 q1、q2、q3。三者須各為 1–10 且互不相同，否則重新輸入完整三個數值。輸入順序可任意，程式會排序。

## 輸出格式

先印不換行的 `Enter the total number of the cookies: `，再印 `Enter 3 different quantities: `。三數不合法，印 `Wrong quantities. Enter three quantities again.` 與換行，重印三數提示。

合法後先印一個換行，再印 `All possibilities:` 與換行。每個解一行，格式 `[x,x,...]`，逗號旁沒有空白，無尾逗號；以指定順序印出。N=0 印 `[]` 與換行。無解印 `There is no way to finish the cookies.` 與換行。非法 N 在 stderr 印 `The total cookie count must be nonnegative.` 與換行並回傳 1；三數讀取失敗清除該行，EOF 正常終止。

## 限制與邊界

0 <= N <= 9223372036854775807；1 <= qi <= 10 且互異。要求輸出全部組合，所需時間與輸出量會隨 N 增大，題目不把 huge N 的大量輸出視為有限常數工作。所有乘法只在不超過 N 的範圍內計算。

## 解法說明

先用三次比較交換令 q1<q2<q3。由小到大枚舉最小數量的天數 n1，再枚舉第二數量的天數 n2。剩餘餅乾 R=N−n1q1−n2q2；若 R%q3=0，n3=R/q3 即為一解。n1升冪符合第一排序；固定n1時，增加n2會增加總天數，因為q2<q3，故n2升冪符合第二排序。直接印三組重複值，無須存全部解。搜尋時間 O((N/q1+1)(N/q2+1))，加上實際輸出時間；額外空間 O(1)。

## 講義可確認的規則

Review P113018 提供數量1–10、互異、do/while、三次比較交換、兩層for加可整除判斷、排序Rule1與組合列印Rule2，以及所有提示與無解訊息。

## 重建版自行補定的規則

N採非負64位整數，N=0的唯一空組合為[]；未依次序排列的原輸入先排序；文字錯誤與EOF處理採上述規格。分隔符管理和64位迴圈是repository修訂。

## 範例與說明

12 個餅乾與 6、2、3 排序成 2、3、6。最先列兩天各吃6，再列3、3、6，接著四天各吃3；隨後才列使用2的組合。第二例N=0只列空組合[]，不需吃任何一天。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
12
6 2 3
```

### 範例 1 輸出

```text
Enter the total number of the cookies: Enter 3 different quantities: 
All possibilities:
[6,6]
[3,3,6]
[3,3,3,3]
[2,2,2,6]
[2,2,2,3,3]
[2,2,2,2,2,2]
```

### 範例 2 輸入

```text
0
1 2 3
```

### 範例 2 輸出

```text
Enter the total number of the cookies: Enter 3 different quantities: 
All possibilities:
[]
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
for (long long dayFirst = 0; dayFirst <= total / first; ++dayFirst) {
    const long long rest = total - dayFirst * first;
    for (long long daySecond = 0; daySecond <= rest / second; ++daySecond) {
        const long long remaining = rest - daySecond * second;
        if (remaining % third != 0) continue;
        const long long dayThird = remaining / third;
        // 按 first、second、third 順序分别印指定天數。
    }
    if (dayFirst == total / first) break; // 防止上界加一溢位。
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
#include <iostream>
#include <limits>

int main()
{
    long long total = 0;
    long long first = 0, second = 0, third = 0;
    std::cout << "Enter the total number of the cookies: ";
    if (!(std::cin >> total) || total < 0) {
        std::cerr << "The total cookie count must be nonnegative.\n";
        return 1;
    }
    bool valid = false;
    do {
        std::cout << "Enter 3 different quantities: ";
        if (std::cin >> first >> second >> third) {
            valid = first >= 1 && first <= 10 && second >= 1 && second <= 10
                    && third >= 1 && third <= 10
                    && first != second && second != third && first != third;
        } else {
            if (std::cin.eof()) return 0;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if (!valid) {
            std::cout << "Wrong quantities. Enter three quantities again.\n";
        }
    } while (!valid);
    long long temporary = 0;
    if (first > second) { temporary = first; first = second; second = temporary; }
    if (second > third) { temporary = second; second = third; third = temporary; }
    if (first > second) { temporary = first; first = second; second = temporary; }

    std::cout << "\nAll possibilities:\n";
    bool possible = false;
    const long long maximumFirst = total / first;
    for (long long dayFirst = 0; dayFirst <= maximumFirst; ++dayFirst) {
        const long long rest = total - dayFirst * first;
        for (long long daySecond = 0; daySecond <= rest / second; ++daySecond) {
            const long long remaining = rest - daySecond * second;
            if (remaining % third != 0) continue;
            const long long dayThird = remaining / third;
            possible = true;
            bool separator = false;
            std::cout << '[';
            for (long long day = 0; day < dayFirst; ++day) {
                if (separator) std::cout << ',';
                std::cout << first;
                separator = true;
            }
            for (long long day = 0; day < daySecond; ++day) {
                if (separator) std::cout << ',';
                std::cout << second;
                separator = true;
            }
            for (long long day = 0; day < dayThird; ++day) {
                if (separator) std::cout << ',';
                std::cout << third;
                separator = true;
            }
            std::cout << "]\n";
        }
        // Avoid an increment past LLONG_MAX for an enormous declared total.
        if (dayFirst == maximumFirst) break;
    }
    if (!possible) std::cout << "There is no way to finish the cookies.\n";
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab05` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab5_2.cpp -o lab5_2
./lab5_2
```

Windows PowerShell 執行 `./lab5_2.exe`。完整原始碼為 [`lab5_2.cpp`](../lab5_2.cpp)；機器可驗證範例在本目錄 `samples.json`。
