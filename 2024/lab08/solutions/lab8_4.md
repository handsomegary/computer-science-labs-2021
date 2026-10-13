# 2024 Lab 8.4　P1130294：數字序列評分

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

將輸入非負整數的十進位數字當作一串符號：1 代表左符號，2 代表右符號，其他數字為零分符號。以下遞迴規則完全定義本重建版的分數，包括未配對的序列：

1. 空序列或單一數字得 0；兩位 `12` 得 1。
2. 從左往右掃描（不含最後一位），遇 1 使 balance 加一、2 減一、其他數字不改變。第一次 balance 成為 0 或 -1 時，將該位含入左段，左右段分數相加。
3. 若沒有可切點，且首位為 1、尾位為 2：內部全部為 1 時得 1；否則內部分數乘 5。
4. 其餘情況刪去最後一位再算。

因此合法配對序列的連接相加、巢狀乘五；未配對與其他數字也有確定結果。不得使用 vector 或 string。

## 輸入

一筆資料，非負十進位整數 x。前導零不保留；例如 0012 以整數 12 評分。

## 輸出

一行十進位分數與換行。負數、超出上限或無法讀取時回傳非零狀態，不印答案。

## 限制

0 ≤ x ≤ 9223372036854775807，最多 19 位數。必須使用遞迴。1…1 得 0、1112 得 1、132 得 0 等特例都依上述一般規則判斷。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
12121122
```

### 範例 1 輸出

```text
7
```
<!-- SAMPLES_END -->

範例說明：12121122 可切成 12、12、1122，分別得 1、1、5，合計 7。

## 解法與核心程式

用整數 10 的次方取得指定位置的數字，以左右位索引表示子序列，遞迴計算切段或內部。allOnes 遞迴檢查特殊內部；避免浮點 pow 對大位數的近似。每次掃描至多 d 位，且 digitAt 透過迴圈計算位值，單次取位最多 O(d)；子問題不斷縮短，總時間上界 O(d³)、堆疊 O(d)。本題 d≤19。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
uint64_t calculate(uint64_t number, int left, int right) {
    if (left <= right) return 0;
    if (left - right == 1 && digitAt(number, left) == 1 && digitAt(number, right) == 2) return 1;
    int symmetry = 0;
    for (int i = left; i > right; --i) {
        if (digitAt(number, i) == 1) ++symmetry;
        else if (digitAt(number, i) == 2) --symmetry;
        if (symmetry == 0 || symmetry == -1)
            return calculate(number, left, i) + calculate(number, i - 1, right);
    }
    if (digitAt(number, left) == 1 && digitAt(number, right) == 2) {
        if (allOnes(number, left - 1, right + 1)) return 1;
        return calculate(number, left - 1, right + 1) * 5;
    }
    return calculate(number, left, right + 1);
}
```

## 講義內容與重建補定

講義已知：講義 `calculate` 圖片可確認單位 0、12=1、balance 切段、內部全 1 特例、內部乘 5 及刪去尾位规則。

自行補定：完整適用於非 1/2 與未配對序列的文字定義、非負 64 位元輸入、純分數輸出及前導零規則為重建版整理／補定；現有核心是圖片 calculate 的整數位值轉寫。

## 完整題解程式

完整可編譯版本：[../lab8_4.cpp](../lab8_4.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P1130294: recursive score rules reproduced from the calculate() hint.
// Neither vector nor string is used.
#include <cstdint>
#include <iostream>
using namespace std;

uint64_t power10(unsigned place) {
    uint64_t result = 1;
    for (unsigned i = 0; i < place; ++i) result *= 10;
    return result;
}
unsigned digitAt(uint64_t number, int place) {
    return static_cast<unsigned>(number / power10(static_cast<unsigned>(place)) % 10);
}
bool allOnes(uint64_t number, int left, int right) {
    if (left < right) return true;
    return digitAt(number, left) == 1 && allOnes(number, left - 1, right);
}
uint64_t calculate(uint64_t number, int left, int right) {
    if (left <= right) return 0;
    if (left - right == 1 && digitAt(number, left) == 1 && digitAt(number, right) == 2) return 1;
    int symmetry = 0;
    for (int i = left; i > right; --i) {
        if (digitAt(number, i) == 1) ++symmetry;
        else if (digitAt(number, i) == 2) --symmetry;
        if (symmetry == 0 || symmetry == -1)
            return calculate(number, left, i) + calculate(number, i - 1, right);
    }
    if (digitAt(number, left) == 1 && digitAt(number, right) == 2) {
        if (allOnes(number, left - 1, right + 1)) return 1;
        return calculate(number, left - 1, right + 1) * 5;
    }
    return calculate(number, left, right + 1);
}
int main() {
    int64_t input;
    if (!(cin >> input) || input < 0) return 1;
    const uint64_t number = static_cast<uint64_t>(input);
    int highest = 0;
    for (uint64_t rest = number; rest >= 10; rest /= 10) ++highest;
    cout << calculate(number, highest, 0) << '\n';
}
```
<!-- SOLUTION_CODE_END -->
