# 2024 Lab 6.4　P113024：兩個鍋子的量米問題

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

兩個鍋子容量分別為 X、Y 公升。一次只能完全裝滿其中一鍋、完全倒空其中一鍋，或把一鍋倒入另一鍋直到來源空了或目標滿了。判斷能否使兩鍋中的米量合計恰好為 Z 公升。

## 輸入

一筆資料，依序為 X、Y、Z 三個十進位整數。

## 輸出

能量出 Z 時印 `1`，否則印 `0`，最後換行。非正容量、相同容量、非正目標或目標超過總容量都印 0。讀取失敗或容量超過指定上限時結束並回傳非零狀態，不印答案。

## 限制

正常資料：1 ≤ X,Y ≤ 2147483647，X≠Y，1 ≤ Z ≤ 9223372036854775807。允許 Z 大於 X+Y，用來驗證不可能案例。計算 X+Y 時必須使用 64 位元整數。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
3 5 4
```

### 範例 1 輸出

```text
1
```
<!-- SAMPLES_END -->

範例說明：容量 3 與 5 的 GCD 為 1，4 不超過總容量 8，所以可以量出 4 公升。

## 解法與核心程式

可量出的量是 GCD(X,Y) 的倍數，且不能超過 X+Y。因此先檢查容量與目標，再算 Euclid GCD，判斷 Z % GCD 是否為 0。時間 O(log min(X,Y))、空間 O(1)。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
bool canMeasureWater(long long x, long long y, long long z) {
    if (x <= 0 || y <= 0 || x == y || z <= 0 || z > x + y) return false;
    return z % gcd(x, y) == 0;
}
```

## 講義內容與重建補定

講義已知：講義給出裝滿／倒空／互倒操作、X≠Y、總容量及 GCD 倍數判斷；圖片函式名為 `canMeasureWater`。

自行補定：明訂量的是兩鍋合計、純 1/0 格式、允許超容量否定案例、正容量範圍與錯誤處理。這些補定與現有 GCD 判斷一致。

## 完整題解程式

完整可編譯版本：[../lab6_4.cpp](../lab6_4.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113024: capacities and their sum are widened before arithmetic.
#include <iostream>
using namespace std;

long long gcd(long long a, long long b) {
    while (b) { const long long remainder = a % b; a = b; b = remainder; }
    return a;
}
bool canMeasureWater(long long x, long long y, long long z) {
    if (x <= 0 || y <= 0 || x == y || z <= 0 || z > x + y) return false;
    return z % gcd(x, y) == 0;
}
int main() {
    long long x, y, z;
    if (!(cin >> x >> y >> z) || x > 2147483647LL || y > 2147483647LL) return 1;
    cout << canMeasureWater(x, y, z) << '\n';
}
```
<!-- SOLUTION_CODE_END -->
