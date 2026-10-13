# 2024 Lab 8.2　P1130292：矩形折半

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

輸入整數長與寬。如果至少一邊為質數，就停止並輸出目前面積；否則將較長邊以整數除法除以 2，再重複判斷。兩邊相等時任選一邊折半結果相同。必須透過遞迴函式完成。

## 輸入

一筆資料，兩個正整數 x、y。

## 輸出

停止時的一行十進位面積。若縮到兩邊皆不大於 1 仍無質數邊，印 `error`；讀取失敗、初始值非正或超過上限也印 error。所有輸出最後換行。

## 限制

1 ≤ x,y ≤ 2147483647。質數必須大於 1，只有 1 與自身兩個因數。面積使用 64 位元整數存放；折半採向下取整，例如 9/2=4。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
8 12
```

### 範例 1 輸出

```text
12
```
<!-- SAMPLES_END -->

範例說明：8×12 → 6×8 → 4×6 → 3×4。3 為質數，停止並輸出 12。

## 解法與核心程式

`prime` 用試除判定，`area` 若已有質數邊即回傳 x*y；否則呼叫 area(max(x,y)/2,min(x,y))。加上 1×1 終止情況，避免原片段無法結束。遞迴深度 O(log max(x,y))；每次質數測試最壞 O(√max(x,y))，額外空間為遞迴堆疊。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
long long area(long long x, long long y) {
    if (prime(x) || prime(y)) return x * y;
    if (x <= 1 && y <= 1) return 0;
    if (x >= y) return area(x / 2, y);
    return area(y / 2, x);
}
```

## 講義內容與重建補定

講義已知：講義流程圖與圖片明定檢查任一邊為質數、折半較長邊，並提供 `area(max(x,y)/2,min(x,y))` 遞迴。

自行補定：單筆純面積格式、正 `int` 初始邊長及無法到達質數邊時的 error 終止為重建版補定。

## 完整題解程式

完整可編譯版本：[../lab8_2.cpp](../lab8_2.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P1130292: integer halving follows the lecture's recursive area hint.
#include <iostream>
using namespace std;

bool prime(long long number) {
    if (number < 2) return false;
    if (number % 2 == 0) return number == 2;
    for (long long divisor = 3; divisor <= number / divisor; divisor += 2)
        if (number % divisor == 0) return false;
    return true;
}
long long area(long long x, long long y) {
    if (prime(x) || prime(y)) return x * y;
    if (x <= 1 && y <= 1) return 0;
    if (x >= y) return area(x / 2, y);
    return area(y / 2, x);
}
int main() {
    long long x, y;
    if (!(cin >> x >> y) || x < 1 || y < 1 || x > 2147483647LL || y > 2147483647LL) {
        cout << "error\n";
        return 1;
    }
    const long long result = area(x, y);
    if (result == 0) cout << "error\n";
    else cout << result << '\n';
}
```
<!-- SOLUTION_CODE_END -->
