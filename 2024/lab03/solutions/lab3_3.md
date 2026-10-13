# 2024 Lab 3.3：Palindrome：數字回文

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

判斷輸入整數的十進位表示是否左右對稱。例如 16461 是回文，12345 不是。重建版將負整數定義為非回文，0 定義為回文。使用 while 與 if/else 完成。

## 輸入格式

輸入一個有號 64 位整數 N。以數值處理，前導零不保留，例如 00100 等同 100。

## 輸出格式

不印輸入提示；回文印 `YES`，非回文印 `NO`，皆加一個換行。數值無法以 64 位整數讀取時，stderr 印 `Invalid integer.` 與換行，回傳 1。

## 限制與邊界

−9223372036854775808 <= N <= 9223372036854775807。正整數末位為 0 時直接判定非回文；0 是例外。

## 解法說明

既有修訂解法只反轉後半位數。將 front 的個位數依序加入 reversed，直到 front <= reversed。偶數位比較 front == reversed；奇數位去掉 reversed 中的中央位再比較。這可避免完整反轉 19 位整數時溢位。時間 O(log10(|N|+1))，額外空間 O(1)。

## 講義可確認的規則

Review 的 P113011 說明回文定義，提供以 % 10、/ 10、while 反轉數字以及印 YES／NO 的程式片段。

## 重建版自行補定的規則

採有號 64 位輸入、負數為非回文、0 為回文、不保留前導零；不印輸入提示。核心採半數反轉，屬 repository 修訂題解而非 Review 原片段逐字轉寫。

## 範例與說明

範例 1 為講義舉例的 16461；範例 2 確認 0 的補定邊界；範例 3 確認負數雖有對稱數字也判定 NO。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
16461
```

### 範例 1 輸出

```text
YES
```

### 範例 2 輸入

```text
0
```

### 範例 2 輸出

```text
YES
```

### 範例 3 輸入

```text
-121
```

### 範例 3 輸出

```text
NO
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
long long front = number;
long long reversed = 0;
while (front > reversed) {
    reversed = reversed * 10 + front % 10;
    front /= 10;
}
if (front == reversed || front == reversed / 10)
    std::cout << "YES\n";
else
    std::cout << "NO\n";
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
#include <iostream>

int main()
{
    long long number = 0;
    if (!(std::cin >> number)) {
        std::cerr << "Invalid integer.\n";
        return 1;
    }
    if (number < 0 || (number > 0 && number % 10 == 0)) {
        std::cout << "NO\n";
        return 0;
    }
    // Reverse only half the digits so even LLONG_MAX cannot overflow.
    long long front = number;
    long long reversed = 0;
    while (front > reversed) {
        reversed = reversed * 10 + front % 10;
        front /= 10;
    }
    if (front == reversed || front == reversed / 10) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab03` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab3_3.cpp -o lab3_3
./lab3_3
```

Windows PowerShell 執行 `./lab3_3.exe`。完整原始碼為 [`lab3_3.cpp`](../lab3_3.cpp)；機器可驗證範例在本目錄 `samples.json`。
