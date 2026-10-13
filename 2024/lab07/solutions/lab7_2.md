# 2024 Lab 7.2　P113026：最後亮著的油燈

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

編號 n 的油燈起初熄滅。每個能整除 n 的正整數代表一次切換，問最後是否亮著。正因數的數量為奇數時燈亮，等價於 n 是完全平方數。重建版另外約定編號 0 按數學上的完全平方數處理，因此也輸出 on。必須透過函式判斷。

## 輸入

一筆非負十進位整數 n。

## 輸出

完全平方數印 `on`，其他印 `off`，最後換行。負數、超過上限或無法讀取時回傳非零狀態，不印答案。

## 限制

0 ≤ n ≤ 9223372036854775807。不可用可能溢位的 `middle*middle` 比較大數；本解使用 `bool isPerfectSquare(uint64_t)`。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
16
```

### 範例 1 輸出

```text
on
```
<!-- SAMPLES_END -->

範例說明：16 的因數有 1、2、4、8、16，共五個，最後亮著，因此印 on。

## 解法與核心程式

非平方數的因數成對出現；平方根所在的因數只出現一次。以整數二分搜尋候選根，使用 middle 與 n/middle 比較，並要求 n%middle=0。搜尋上界為 3037000499，避免浮點平方根誤差；時間 O(log n)、空間 O(1)。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
bool isPerfectSquare(uint64_t number) {
    if (number == 0) return true;
    uint64_t low = 1, high = number < 3037000499ULL ? number : 3037000499ULL;
    while (low <= high) {
        const uint64_t middle = low + (high - low) / 2;
        const uint64_t quotient = number / middle;
        if (middle == quotient && number % middle == 0) return true;
        if (middle > quotient) high = middle - 1;
        else low = middle + 1;
    }
    return false;
}
```

## 講義內容與重建補定

講義已知：講義明確說明奇數因數代表燈亮、完全平方數判斷、至少一個函式，並列出平方根／二分搜尋方法。

自行補定：單筆輸入、64 位元非負範圍、`on`／`off` 字樣、0 的處理及拒絕負號包回由重建版補定。

## 完整題解程式

完整可編譯版本：[../lab7_2.cpp](../lab7_2.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113026: a lamp remains on precisely at a perfect-square index.
#include <cstdint>
#include <iostream>
using namespace std;

bool isPerfectSquare(uint64_t number) {
    if (number == 0) return true;
    uint64_t low = 1, high = number < 3037000499ULL ? number : 3037000499ULL;
    while (low <= high) {
        const uint64_t middle = low + (high - low) / 2;
        const uint64_t quotient = number / middle;
        if (middle == quotient && number % middle == 0) return true;
        if (middle > quotient) high = middle - 1;
        else low = middle + 1;
    }
    return false;
}
int main() {
    int64_t input;
    if (!(cin >> input) || input < 0) return 1;
    const uint64_t number = static_cast<uint64_t>(input);
    cout << (isPerfectSquare(number) ? "on" : "off") << '\n';
}
```
<!-- SOLUTION_CODE_END -->
