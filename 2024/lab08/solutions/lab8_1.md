# 2024 Lab 8.1　P1130291：組合數計算器

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

從 m 個不同物件中選 n 個，不考慮挑選順序，求組合數 C(m,n)=m!/(n!(m-n)!)。必須使用遞迴計算，並輸出完整精確整數，不得用浮點近似或溢位後的階乘作答案。

## 輸入

一筆資料，依序為非負整數 m、n。

## 輸出

一行 `ans: V`，V 為完整十進位組合數。m、n 為負數、n>m、m 超出解析上限或讀取失敗時印 `error` 並回傳非零狀態。

## 限制

重建基本測資：0 ≤ n ≤ m ≤ 1000。程式可解析 m≤4294967295，但結果位數和運算量依 n 增加。C(0,0)=1，C(m,0)=C(m,m)=1。必須使用至少一個遞迴運算函式。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
5 2
```

### 範例 1 輸出

```text
ans: 10
```
<!-- SAMPLES_END -->

範例說明：C(5,2)=5×4/(2×1)=10。

## 解法與核心程式

先用對稱性取 k=min(n,m-n)。從 result=1 開始，依序 result*=m-k+i、result/=i，i=1…k；每一步都整除。以十進位字串做精確乘除，避開直接 m! 的 64 位元溢位。把 i 區間遞迴分半，但左半先完成後才算右半，使步驟順序保持正確，遞迴深度 O(log k)。若最大中間位數為 d，運算時間 O(kd)、字串空間 O(d)。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
void combinationSteps(uint32_t m, uint32_t n, uint32_t first, uint32_t last, Natural &result) {
    if (first > last) return;
    if (first == last) {
        result.multiply(m - n + first);
        result.divide(first);
        return;
    }
    const uint32_t middle = first + (last - first) / 2;
    combinationSteps(m, n, first, middle, result);
    combinationSteps(m, n, middle + 1, last, result);
}
```

## 講義內容與重建補定

講義已知：講義給出組合公式、遞迴要求、階乘函式提示及 `ans:` 標籤。只要求遞迴計算 C(m,n)，未限制必須直接存固定寬度的 m!。

自行補定：輸入先 m 後 n、基本測資 m≤1000、精確大整數、0 的定義與非法資料處理由重建版補定。現有解法核心是組合數乘除遞迴，不是講義階乘片段的逐行轉寫。

## 完整題解程式

完整可編譯版本：[../lab8_1.cpp](../lab8_1.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P1130291: exact combinations, with a recursive calculation.
#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

class Natural {
    string digits;
public:
    Natural() : digits("1") {}
    void multiply(uint32_t factor) {
        uint64_t carry = 0;
        for (size_t i = digits.size(); i > 0; --i) {
            carry += static_cast<uint64_t>(digits[i - 1] - '0') * factor;
            digits[i - 1] = static_cast<char>('0' + carry % 10);
            carry /= 10;
        }
        while (carry) {
            digits.insert(digits.begin(), static_cast<char>('0' + carry % 10));
            carry /= 10;
        }
    }
    void divide(uint32_t divisor) {
        uint64_t remainder = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            remainder = remainder * 10 + static_cast<unsigned>(digits[i] - '0');
            digits[i] = static_cast<char>('0' + remainder / divisor);
            remainder %= divisor;
        }
        const size_t first = digits.find_first_not_of('0');
        digits = first == string::npos ? "0" : digits.substr(first);
    }
    const string &text() const { return digits; }
};

// Process the binomial recurrence in order; split the call tree to keep
// recursion depth logarithmic while preserving exact division at each step.
void combinationSteps(uint32_t m, uint32_t n, uint32_t first, uint32_t last, Natural &result) {
    if (first > last) return;
    if (first == last) {
        result.multiply(m - n + first);
        result.divide(first);
        return;
    }
    const uint32_t middle = first + (last - first) / 2;
    combinationSteps(m, n, first, middle, result);
    combinationSteps(m, n, middle + 1, last, result);
}
int main() {
    long long m, n;
    if (!(cin >> m >> n) || m < 0 || n < 0 || n > m || m > 4294967295LL) {
        cout << "error\n";
        return 1;
    }
    if (n > m - n) n = m - n;
    Natural result;
    combinationSteps(static_cast<uint32_t>(m), static_cast<uint32_t>(n), 1,
                     static_cast<uint32_t>(n), result);
    cout << "ans: " << result.text() << '\n';
}
```
<!-- SOLUTION_CODE_END -->
