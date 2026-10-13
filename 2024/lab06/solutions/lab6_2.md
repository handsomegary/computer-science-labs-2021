# 2024 Lab 6.2　P113022：最小公倍數

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

給定兩個正整數 a、b，求同時為兩者倍數的最小正整數。必須透過 `int LCM_calculator(int, int)` 回傳答案，不得用全域變數傳遞結果。

## 輸入

一筆資料，依序為兩個十進位整數 a、b，以空白或換行分隔。

## 輸出

合法時輸出 LCM 的十進位數值與換行。讀取失敗、任一數不為正數，或答案超出 `int` 時輸出 `error`，回傳非零狀態。沒有輸入提示或答案標籤。

## 限制

1 ≤ a,b ≤ 2147483647；正常答案資料另滿足 LCM(a,b) ≤ 2147483647。溢位案例屬明定的錯誤處理資料。指定函式回傳型態必須維持 `int`。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
21 6
```

### 範例 1 輸出

```text
42
```
<!-- SAMPLES_END -->

範例說明：21 與 6 的 GCD 為 3，所以 LCM = 21/3×6 = 42。

## 解法與核心程式

利用 LCM(a,b)=a/GCD(a,b)×b。先用 Euclid 餘數迴圈求 GCD，先除再以 64 位元乘法算候選答案，檢查範圍後轉回 `int`。相比講義逐個試候選倍數，時間縮短為 O(log min(a,b))、空間 O(1)。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
int LCM_calculator(int a, int b) {
    if (a <= 0 || b <= 0) throw invalid_argument("positive integers required");
    int x = a, y = b;
    while (y) { const int remainder = x % y; x = y; y = remainder; }
    const long long lcm = static_cast<long long>(a / x) * b;
    if (lcm > numeric_limits<int>::max()) throw overflow_error("LCM exceeds int");
    return static_cast<int>(lcm);
}
```

## 講義內容與重建補定

講義已知：講義指定兩個整數、`int LCM_calculator(...)` 與函式回傳；圖片示範逐一檢查公倍數。

自行補定：正數輸入、單筆純數值格式及超過 `int` 回報 `error` 為重建版補定。題解使用等價且較快的 GCD 演算法，並非照抄逐一試數。

## 完整題解程式

完整可編譯版本：[../lab6_2.cpp](../lab6_2.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113022: int return type is retained; overflow is reported explicitly.
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

int LCM_calculator(int a, int b) {
    if (a <= 0 || b <= 0) throw invalid_argument("positive integers required");
    int x = a, y = b;
    while (y) { const int remainder = x % y; x = y; y = remainder; }
    const long long lcm = static_cast<long long>(a / x) * b;
    if (lcm > numeric_limits<int>::max()) throw overflow_error("LCM exceeds int");
    return static_cast<int>(lcm);
}
int main() {
    int a, b;
    if (!(cin >> a >> b)) { cout << "error\n"; return 1; }
    try { cout << LCM_calculator(a, b) << '\n'; }
    catch (const exception &) { cout << "error\n"; return 1; }
}
```
<!-- SOLUTION_CODE_END -->
