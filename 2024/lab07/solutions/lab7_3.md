# 2024 Lab 7.3　P113027：Almost Prime 計數與進位轉換

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

本重建版正式定義 Almost Prime 為恰好含兩個質因數、含重複次數的正整數，即 semiprime：n=p×q，p、q 都為質數，可以相同。例如 4、6、9、10 符合，8=2³ 不符合。計算閉區間 [a,b] 中符合條件的個數，並把這個個數輸出為十進位、二進位及十六進位。

## 輸入

一筆資料，區間下限 a、上限 b，以空白或換行分隔。

## 輸出

依序輸出三行：`decimal: D`、`binary: B`、`hex: H`。不加進位前綴或前導零；十六進位字母使用 A–F。計數為 0 時，三種表示都為 `0`。負數、a>b、超過解析上限或讀取失敗時回傳非零狀態，不印答案。

## 限制

重建基本測資：0 ≤ a ≤ b ≤ 1000000，區間長度 b-a+1 ≤ 100000。程式本身可解析至 9223372036854775807，但試除法不保證極大區間的執行時間。不得宣告陣列、vector 或 `std::string`；至少一個函式處理計算。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
4 10
```

### 範例 1 輸出

```text
decimal: 4
binary: 100
hex: 4
```
<!-- SAMPLES_END -->

範例說明：[4,10] 有 4、6、9、10 四個 semiprime，4 的二進位為 100，十六進位為 4。

## 解法與核心程式

對區間每個數，逐個質因數相除，累計 multiplicity；剩餘值大於 1 時再計一個質因數。總重數恰為 2 才計入。二進位與十六進位用遞迴先印商再印餘數，因此不需陣列或字串。試除計數時間上界 O((b-a+1)√b)、額外空間 O(log D) 來自進位輸出遞迴。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
bool almostPrime(uint64_t number) {
    if (number < 4) return false;
    unsigned multiplicity = 0, distinct = 0;
    for (uint64_t divisor = 2; divisor <= number / divisor; divisor += divisor == 2 ? 1 : 2) {
        if (number % divisor != 0) continue;
        ++distinct;
        do { number /= divisor; ++multiplicity; } while (number % divisor == 0);
        if (ALMOST_PRIME_MODE == 0 && multiplicity > 2) return false;
        if (ALMOST_PRIME_MODE == 1 && distinct > 1) return false;
        if (ALMOST_PRIME_MODE == 2 && distinct > 2) return false;
    }
    if (number > 1) { ++multiplicity; ++distinct; }
    if (ALMOST_PRIME_MODE == 1) return distinct == 1 && multiplicity >= 2;
    if (ALMOST_PRIME_MODE == 2) return distinct == 2;
    return multiplicity == 2;
}
```

## 講義內容與重建補定

講義已知：講義提到區間內 Almost Prime 數量、檢查 2 到平方根的因數、函式、進位轉換，以及不準陣列／vector／string。沒有提供 Almost Prime 的精確定義及輸出格式。

自行補定：重建版採 semiprime、三行進位格式、上下限先後、實用測資範圍。它們是正式補定的本 repo 題意，不是教授原題。延伸：編譯 `-DALMOST_PRIME_MODE=1` 可改成 prime powers p^k(k≥2)，`=2` 可改成恰好兩個不同質因數；延伸模式不改三行輸出格式。

## 完整題解程式

完整可編譯版本：[../lab7_3.cpp](../lab7_3.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113027 Review reference implementation.
// The provided slides omit the original definition and output contract.
// Default: exactly two prime factors, counting multiplicity (semiprime).
// -DALMOST_PRIME_MODE=1: prime powers p^k, k>=2.
// -DALMOST_PRIME_MODE=2: exactly two distinct prime factors.
// No array, vector, or std::string is used.
#include <cstdint>
#include <iostream>
using namespace std;

#ifndef ALMOST_PRIME_MODE
#define ALMOST_PRIME_MODE 0
#endif
static_assert(ALMOST_PRIME_MODE >= 0 && ALMOST_PRIME_MODE <= 2, "mode must be 0, 1, or 2");

bool almostPrime(uint64_t number) {
    if (number < 4) return false;
    unsigned multiplicity = 0, distinct = 0;
    for (uint64_t divisor = 2; divisor <= number / divisor; divisor += divisor == 2 ? 1 : 2) {
        if (number % divisor != 0) continue;
        ++distinct;
        do { number /= divisor; ++multiplicity; } while (number % divisor == 0);
        if (ALMOST_PRIME_MODE == 0 && multiplicity > 2) return false;
        if (ALMOST_PRIME_MODE == 1 && distinct > 1) return false;
        if (ALMOST_PRIME_MODE == 2 && distinct > 2) return false;
    }
    if (number > 1) { ++multiplicity; ++distinct; }
    if (ALMOST_PRIME_MODE == 1) return distinct == 1 && multiplicity >= 2;
    if (ALMOST_PRIME_MODE == 2) return distinct == 2;
    return multiplicity == 2;
}
uint64_t countAlmostPrimes(uint64_t lower, uint64_t upper) {
    uint64_t count = 0;
    if (lower > upper) return 0;
    for (uint64_t number = lower; ; ++number) {
        if (almostPrime(number)) ++count;
        if (number == upper) break;
    }
    return count;
}
void printBase(uint64_t number, unsigned base) {
    if (number >= base) printBase(number / base, base);
    const unsigned digit = static_cast<unsigned>(number % base);
    cout << static_cast<char>(digit < 10 ? '0' + digit : 'A' + digit - 10);
}
int main() {
    int64_t lowerInput, upperInput;
    if (!(cin >> lowerInput >> upperInput) || lowerInput < 0 || upperInput < lowerInput) return 1;
    const uint64_t lower = static_cast<uint64_t>(lowerInput);
    const uint64_t upper = static_cast<uint64_t>(upperInput);
    const uint64_t count = countAlmostPrimes(lower, upper);
    cout << "decimal: " << count << "\nbinary: ";
    printBase(count, 2);
    cout << "\nhex: ";
    printBase(count, 16);
    cout << '\n';
}
```
<!-- SOLUTION_CODE_END -->
