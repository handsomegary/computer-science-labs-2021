# 2024 Lab 9.3　P113031：字典序排列

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

輸入 n 個互不相同的整數，列出它們的全部排列。輸出順序為字典序遞增：比較第一個不同位置，其值較小者在前。輸入初始順序可任意，必須從最小排列開始，直到最大（完全遞減）排列。

## 輸入

一筆資料，先正整數 n，再 n 個帶符號64位元整數，以空白或換行分隔。

## 輸出

每個排列一行，各數字以一個空格隔開，不加行首／行尾空格。不存在提示或數量標籤。n 無效、陣列配置失敗或重複值時印 `error` 並回傳非零狀態；元素讀取失败時直接回傳非零狀態。

## 限制

重建基本測資1≤n≤9；元素互異，範圍-9223372036854775808至9223372036854775807。程式大小解析上限為2147483647，但 n! 輸出量本身使大型 n 不適用。必須使用陣列；本題要求自己實現 pivot／successor／suffix，不调用 std::next_permutation。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
3
2 1 3
```

### 範例 1 輸出

```text
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```
<!-- SAMPLES_END -->

範例說明：輸入2、1、3先排成1、2、3；三個互異數有3!=6個排列，範例列出全部六行。

## 解法與核心程式

先用插入排序排成遞增。每次從右找 values[pivot]<values[pivot+1]，找右側最末的大於 pivot 值，交換，再反轉 pivot 後綴。若找不到 pivot，已是最大排列而停止。初始化 O(n²)，列出排列時間 O(n×n!)、陣列空間 O(n)。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
bool nextPermutation(long long *values, long long size) {
    long long pivot = size - 2;
    while (pivot >= 0 && values[pivot] >= values[pivot + 1]) --pivot;
    if (pivot < 0) return false;
    long long successor = size - 1;
    while (values[successor] <= values[pivot]) --successor;
    swapElements(values, pivot, successor);
    reverseSuffix(values, pivot + 1, size - 1);
    return true;
}
```

## 講義內容與重建補定

講義已知：講義明定互異整數、全部字典序排列直到遞減，並提供 pivot、右側successor、swap與reverse片段。

自行補定：n在前的完整輸入、純排列格式、初始輸入可未排序、重建 n≤9 及拒絕重複值的行為為補定。

## 完整題解程式

完整可編譯版本：[../lab9_3.cpp](../lab9_3.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113031: array-based, manual lexicographic next permutation.
#include <iostream>
#include <memory>
#include <new>
using namespace std;

void swapElements(long long *values, long long a, long long b) {
    const long long temporary = values[a];
    values[a] = values[b];
    values[b] = temporary;
}
void reverseSuffix(long long *values, long long start, long long end) {
    while (start < end) swapElements(values, start++, end--);
}
bool nextPermutation(long long *values, long long size) {
    long long pivot = size - 2;
    while (pivot >= 0 && values[pivot] >= values[pivot + 1]) --pivot;
    if (pivot < 0) return false;
    long long successor = size - 1;
    while (values[successor] <= values[pivot]) --successor;
    swapElements(values, pivot, successor);
    reverseSuffix(values, pivot + 1, size - 1);
    return true;
}
int main() {
    long long size;
    if (!(cin >> size) || size < 1 || size > 2147483647LL) { cout << "error\n"; return 1; }
    unique_ptr<long long[]> values;
    try { values.reset(new long long[static_cast<size_t>(size)]); }
    catch (const bad_alloc &) { cout << "error\n"; return 1; }
    for (long long i = 0; i < size; ++i) if (!(cin >> values[static_cast<size_t>(i)])) return 1;
    // Start at the first permutation, so an unsorted input still emits all
    // permutations as required, instead of only its lexicographic suffix.
    for (long long i = 1; i < size; ++i) {
        const long long value = values[static_cast<size_t>(i)];
        long long j = i;
        while (j > 0 && values[static_cast<size_t>(j - 1)] > value) {
            values[static_cast<size_t>(j)] = values[static_cast<size_t>(j - 1)];
            --j;
        }
        values[static_cast<size_t>(j)] = value;
    }
    for (long long i = 1; i < size; ++i) {
        if (values[static_cast<size_t>(i - 1)] == values[static_cast<size_t>(i)]) {
            cout << "error\n";
            return 1;
        }
    }
    do {
        for (long long i = 0; i < size; ++i) {
            if (i) cout << ' ';
            cout << values[static_cast<size_t>(i)];
        }
        cout << '\n';
    } while (nextPermutation(values.get(), size));
}
```
<!-- SOLUTION_CODE_END -->
