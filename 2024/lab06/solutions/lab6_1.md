# 2024 Lab 6.1　P113021：三個數的最小值

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

輸入三個有限浮點數，找出其中最小的數。必須將三個數傳入 `double minimum(double, double, double)`，由函式回傳答案，再由 `main` 輸出；不得用全域變數傳遞計算結果。相等時保留第一次取得的最小值。

## 輸入

一筆資料，依序為 x、y、z，三個數以空白或換行分隔。數字可為正數、負數或零，可使用一般十進位或科學記號。

## 輸出

只輸出最小值及一個換行，不加提示文字。採 C++ `defaultfloat`、15 位有效數字；這是有效數字上限，不是固定 15 位小數。讀取失敗、無法表示成有限 `double` 或非有限數值時印 `error`，程式回傳非零狀態。

## 限制

三個數都須能以有限 `double` 表示。不得用 NaN 或無限大作合法測資。本題沒有陣列、迴圈或排序需求。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
3.25 -2.5 9.75
```

### 範例 1 輸出

```text
-2.5
```
<!-- SAMPLES_END -->

範例說明：三個數中 -2.5 最小，因此只輸出 -2.5。

## 解法與核心程式

先把結果設成 x，再分別比較 y、z；較小時更新。只用兩次比較，時間 O(1)、額外空間 O(1)。不相等的比較使用 `<`，因此重複最小值不需要額外分支。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
double minimum(double x, double y, double z) {
    double result = x;
    if (y < result) result = y;
    if (z < result) result = z;
    return result;
}
```

## 講義內容與重建補定

講義已知：講義明定三個浮點數、指定 `double minimum(...)` 及回傳值，並提供逐次比較的函式碼圖片。

自行補定：完整單筆輸入、有限數限制、純數值輸出、15 位有效數字，以及非法資料的錯誤行為由重建版補定。

## 完整題解程式

完整可編譯版本：[../lab6_1.cpp](../lab6_1.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113021: return the minimum through the required function.
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

double minimum(double x, double y, double z) {
    double result = x;
    if (y < result) result = y;
    if (z < result) result = z;
    return result;
}
int main() {
    double x, y, z;
    if (!(cin >> x >> y >> z) || !isfinite(x) || !isfinite(y) || !isfinite(z)) {
        cout << "error\n";
        return 1;
    }
    cout << setprecision(15) << minimum(x, y, z) << '\n';
}
```
<!-- SOLUTION_CODE_END -->
