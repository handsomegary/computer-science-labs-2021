# 2024 Lab 8.3　P1130293：糖果分配路徑

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

有 N 顆糖果與三個可選擇的發放量 a、b、c。每一步選其中一種量扣除，不能使剩餘量為負，問有多少個有序選擇序列能剛好扣到 0。a、b、c 由一個三位數的百、十、個位取得。若數字相同，也視為不同種類的選擇，例如 111 每一步有三種選擇。必須使用遞迴，不能使用 vector 或 string。

## 輸入

一筆資料：先輸入非負總數 N，再輸入三位整數 abc。a、b、c 都必須為 1–9。

## 輸出

一行十進位有序路徑數；N=0 時有一個空序列，輸出 1。abc 不為三位數、任一位為 0、N 為負數／超出 `unsigned`、解析失敗、記憶體配置失敗，或所需最終答案超出 64 位元無號整數時，印 `error` 並回傳非零狀態。無關中間狀態溢位不應誤報。

## 限制

重建基本測資：0 ≤ N ≤ 100000，100 ≤ abc ≤ 999，三個數字皆非 0。正常計數資料的答案≤18446744073709551615；可另提供溢位錯誤案例。程式 N 的儲存上限為 `unsigned` 最大值（一般為4294967295），仍受配置與平台大小限制。允許陣列 memoization。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
4 123
```

### 範例 1 輸出

```text
7
```
<!-- SAMPLES_END -->

範例說明：N=4、步長為 1、2、3，有 1111、112、121、211、22、13、31 共七條路徑。

## 解法與核心程式

令 ways(0)=1，ways(x)=ways(x-a)+ways(x-b)+ways(x-c)，只加非負索引。memo 保存結果，known 保存是否計算，overflow 單獨標記溢位並傳播到依賴狀態。以平衡遞迴從小到大填表，使 remain 只遞迴到已知狀態，避免深度等於 N。時間 O(N)、陣列空間 O(N)、呼叫深度 O(log N)。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
uint64_t remain(unsigned amount, unsigned a, unsigned b, unsigned c,
                uint64_t *memo, bool *known, bool *overflow) {
    if (amount == 0) return 1;
    if (known[amount]) return memo[amount];
    uint64_t total = 0;
    for (unsigned choice = 0; choice < 3; ++choice) {
        const unsigned step = choice == 0 ? a : choice == 1 ? b : c;
        if (step > amount) continue;
        const uint64_t count = remain(amount - step, a, b, c, memo, known, overflow);
        if (overflow[amount - step] || count > numeric_limits<uint64_t>::max() - total) {
            overflow[amount] = true;
            total = numeric_limits<uint64_t>::max();
        } else total += count;
    }
    known[amount] = true;
    memo[amount] = total;
    return total;
}
```

## 講義內容與重建補定

講義已知：講義要求遞迴、禁止 vector/string、拆三位數；`remain` 圖片對 a、b、c 分別減一次，再遞迴，因此它計的是有序路徑，重複位數仍有不同分支。

自行補定：總數在前、三位數在後、0 的空路徑、拒絕零步長、基本資料上限、精確 64 位元範圍及溢位行為均為重建版補定。陣列 memoization 是現有解法的效率改善。

## 完整題解程式

完整可編譯版本：[../lab8_3.cpp](../lab8_3.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P1130293: count ordered subtraction paths for the three digit choices.
// Array memoization is permitted; no vector or string is used.
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>
using namespace std;

uint64_t remain(unsigned amount, unsigned a, unsigned b, unsigned c,
                uint64_t *memo, bool *known, bool *overflow) {
    if (amount == 0) return 1;
    if (known[amount]) return memo[amount];
    uint64_t total = 0;
    for (unsigned choice = 0; choice < 3; ++choice) {
        const unsigned step = choice == 0 ? a : choice == 1 ? b : c;
        if (step > amount) continue;
        const uint64_t count = remain(amount - step, a, b, c, memo, known, overflow);
        if (overflow[amount - step] || count > numeric_limits<uint64_t>::max() - total) {
            overflow[amount] = true;
            total = numeric_limits<uint64_t>::max();
        } else total += count;
    }
    known[amount] = true;
    memo[amount] = total;
    return total;
}

// Fill smaller amounts first via balanced recursion. remain() then recurses
// only into cached states, avoiding a call stack proportional to candy count.
void fillCounts(unsigned first, unsigned last, unsigned a, unsigned b, unsigned c,
                uint64_t *memo, bool *known, bool *overflow) {
    if (first > last) return;
    if (first == last) { remain(first, a, b, c, memo, known, overflow); return; }
    const unsigned middle = first + (last - first) / 2;
    fillCounts(first, middle, a, b, c, memo, known, overflow);
    fillCounts(middle + 1, last, a, b, c, memo, known, overflow);
}
int main() {
    int64_t amountInput, choicesInput;
    if (!(cin >> amountInput >> choicesInput) || amountInput < 0 ||
        static_cast<uint64_t>(amountInput) > numeric_limits<unsigned>::max() ||
        choicesInput < 100 || choicesInput > 999) {
        cout << "error\n";
        return 1;
    }
    const unsigned amount = static_cast<unsigned>(amountInput);
    const unsigned choices = static_cast<unsigned>(choicesInput);
    const unsigned a = choices / 100, b = choices / 10 % 10, c = choices % 10;
    if (a == 0 || b == 0 || c == 0) { cout << "error\n"; return 1; }
    try {
        if (static_cast<uint64_t>(amount) >= numeric_limits<size_t>::max()) {
            cout << "error\n";
            return 1;
        }
        const size_t size = static_cast<size_t>(amount) + 1;
        unique_ptr<uint64_t[]> memo(new uint64_t[size]());
        unique_ptr<bool[]> known(new bool[size]());
        unique_ptr<bool[]> overflow(new bool[size]());
        fillCounts(1, amount, a, b, c, memo.get(), known.get(), overflow.get());
        const uint64_t result = remain(amount, a, b, c, memo.get(), known.get(), overflow.get());
        if (overflow[amount]) throw overflow_error("count overflow");
        cout << result << '\n';
    } catch (const exception &) { cout << "error\n"; return 1; }
}
```
<!-- SOLUTION_CODE_END -->
