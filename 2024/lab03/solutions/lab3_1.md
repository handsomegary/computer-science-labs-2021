# 2024 Lab 3.1：Candy Bar：糖果吧開店狀態

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

糖果吧最初有 N 顆糖果。只要還有糖果，就宣告開店並讓使用者輸入本次拿取顆數。拿取數量至少等於剩餘數量時，糖果視為全部取完；否則扣除本次拿取顆數。沒有糖果後，宣告關店並結束。請使用 while 迴圈實作。

## 輸入格式

第一個整數是初始總數 N。之後依序輸入每次拿取數量 T，數值以空白或換行分隔。N = 0 時不用提供 T。正常測資的拿取序列應能使糖果耗盡；T = 0 合法，但不減少剩餘數量。

## 輸出格式

沒有初始輸入提示。每次開始拿取前，依序輸出 `The candy bar is open!` 與換行，再輸出 `How many candy do you want to take: `，冒號後有一個空格、沒有換行。耗盡後輸出 `The candy bar is closed!` 與換行。

拿取數值為負或讀取失敗時重新輸入，提示 `Invalid candy count. Enter again: `；文字造成讀取失敗時清除該行。初始總數不合法時，在 stderr 輸出 `The total candy count must be nonnegative.` 與換行，回傳 1。拿取階段遇到 EOF 回傳 0，不偽造關店訊息。

## 限制與邊界

合法 N、T 的範圍皆為 0–9223372036854775807。重建版採 64 位有號整數，不計算可能溢位的負剩餘值。正常題目輸出僅使用 stdout；範例沒有終端機輸入回顯。

## 解法說明

維持剩餘糖果 remaining。在 while (remaining > 0) 內印提示、取得合法 taken；taken >= remaining 時直接令 remaining = 0，否則相減。這比先相減更容易防止邊界溢位。時間 O(有效拿取次數 + 重試次數)，額外空間 O(1)。

## 講義可確認的規則

Review 的 P113009 指定 while，並提供開店、拿取與關店訊息；程式片段以 total > 0 持續扣掉 candy。

## 重建版自行補定的規則

初始總數不印提示；總數與拿取數量皆為非負 64 位整數；允許零拿取；超額拿取直接耗盡；非法輸入與 EOF 行為以上述輸出規格為準。這些補定已成為本 repository 的明確題目規則。

## 範例與說明

範例 1：10 顆先拿 3、再拿 7，開店提示印兩次後關店。範例 2：初始總數是下界 0，因此立即關店。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
10
3
7
```

### 範例 1 輸出

```text
The candy bar is open!
How many candy do you want to take: The candy bar is open!
How many candy do you want to take: The candy bar is closed!
```

### 範例 2 輸入

```text
0
```

### 範例 2 輸出

```text
The candy bar is closed!
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
while (remaining > 0) {
    // 印出已定義的開店與拿取提示，讀取合法 taken。
    if (taken >= remaining) remaining = 0;
    else remaining -= taken;
}
std::cout << "The candy bar is closed!\n";
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 Lab 3.1: the Review does not provide an initial total-candy prompt.
#include <iostream>
#include <limits>

int main()
{
    long long remaining = 0;
    if (!(std::cin >> remaining) || remaining < 0) {
        std::cerr << "The total candy count must be nonnegative.\n";
        return 1;
    }
    while (remaining > 0) {
        std::cout << "The candy bar is open!\n";
        std::cout << "How many candy do you want to take: ";
        long long taken = 0;
        while (!(std::cin >> taken) || taken < 0) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid candy count. Enter again: ";
        }
        // Taking at least the remaining amount empties the bar without overflow.
        if (taken >= remaining) {
            remaining = 0;
        } else {
            remaining -= taken;
        }
    }
    std::cout << "The candy bar is closed!\n";
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab03` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab3_1.cpp -o lab3_1
./lab3_1
```

Windows PowerShell 執行 `./lab3_1.exe`。完整原始碼為 [`lab3_1.cpp`](../lab3_1.cpp)；機器可驗證範例在本目錄 `samples.json`。
