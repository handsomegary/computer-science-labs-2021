# 2024 Lab 3.2：Height Limitation：遊樂設施身高門檻

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

輸入三人的身高及欲搭乘的遊樂設施編號，計算符合最低身高的人數。設施 1 最低 140、設施 2 最低 120、設施 3 最低 100；身高剛好等於門檻也可以搭乘。使用 if/else 選擇門檻並判斷三人。

## 輸入格式

依序為三個非負身高實數 H1、H2、H3，以及一個整數設施編號 R。四個數值以空白或換行分隔；身高單位為公分。

## 輸出格式

不印任何輸入提示。合法輸入時只輸出可搭乘人數 0、1、2 或 3，再換行。

身高不合法或數值讀取失敗時，stderr 輸出 `Enter three nonnegative heights and a ride number.`，回傳 1。成功取得三個合法身高但 R 不是 1–3 時，stderr 輸出 `Ride must be 1, 2, or 3.`，回傳 1。兩種錯誤訊息皆以換行結束。

## 限制與邊界

H1、H2、H3 必須是 double 可表示的有限非負數，0 也合法；R 必須是 1、2、3。依目前 C++11 編譯環境，double 為一般 64 位浮點數。

## 解法說明

先以 if/else 找到 minimumHeight，再各自檢查三個高度是否 >= minimumHeight，符合時增加 people。沒有排序需求，時間與額外空間都是 O(1)。

## 講義可確認的規則

Review 的 P113010 指定 if/else，程式圖碼以 h < 140／120／100 排除不符合者，確認門檻為含等號。

## 重建版自行補定的規則

身高單位為公分、允許有限非負實數；直接讀四個數值、不印提示；結果只印人數。讀取錯誤處理亦採上述規格。這是重建題的完整介面。

## 範例與說明

範例 1：139 不達 140，140 與 150 符合，因此輸出 2。範例 2：設施 2 的門檻 120 含等號，119.9 不符合。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
139 140 150 1
```

### 範例 1 輸出

```text
2
```

### 範例 2 輸入

```text
120 120 119.9 2
```

### 範例 2 輸出

```text
2
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
int minimumHeight = 0;
if (ride == 1) minimumHeight = 140;
else if (ride == 2) minimumHeight = 120;
else if (ride == 3) minimumHeight = 100;
int people = 0;
if (first >= minimumHeight) ++people;
if (second >= minimumHeight) ++people;
if (third >= minimumHeight) ++people;
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// The Review supplies ride thresholds, but no literal input/output prompts.
#include <cmath>
#include <iostream>

int main()
{
    double first = 0.0;
    double second = 0.0;
    double third = 0.0;
    int ride = 0;
    if (!(std::cin >> first >> second >> third >> ride)
        || !std::isfinite(first) || !std::isfinite(second) || !std::isfinite(third)
        || first < 0 || second < 0 || third < 0) {
        std::cerr << "Enter three nonnegative heights and a ride number.\n";
        return 1;
    }
    int minimumHeight = 0;
    if (ride == 1) {
        minimumHeight = 140;
    } else if (ride == 2) {
        minimumHeight = 120;
    } else if (ride == 3) {
        minimumHeight = 100;
    } else {
        std::cerr << "Ride must be 1, 2, or 3.\n";
        return 1;
    }
    int people = 0;
    if (first >= minimumHeight) {
        ++people;
    }
    if (second >= minimumHeight) {
        ++people;
    }
    if (third >= minimumHeight) {
        ++people;
    }
    std::cout << people << '\n';
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab03` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab3_2.cpp -o lab3_2
./lab3_2
```

Windows PowerShell 執行 `./lab3_2.exe`。完整原始碼為 [`lab3_2.cpp`](../lab3_2.cpp)；機器可驗證範例在本目錄 `samples.json`。
