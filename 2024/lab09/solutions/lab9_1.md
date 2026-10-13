# 2024 Lab 9.1　P1130295：奇數陣列索引

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

建立含十個元素的陣列，第 i 個元素（從 0 起算）為 1+2i，因此內容為 1、3、5、…、19。讀入索引並輸出對應元素。索引無效時重新輸入。

## 輸入

一個索引 i。若索引不在 0–9 或無法以整數讀取，提供下一筆索引直到有效為止。非法文字的重試資料以換行分隔；EOF 結束。

## 輸出

每次先印 `Please enter the index of the element (0 to 9): ` 再換行。無效時印 `Invalid index. Please enter a value between 0 and 9.` 與換行，再印提示。有效時只印對應元素及換行並結束。完整 stdout 不含終端機的輸入回顯。

## 限制

有效索引0≤i≤9。必須真的建立十元素陣列，不可直接用公式代替取陣列值；公式只用於初始化。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
-1
5
```

### 範例 1 輸出

```text
Please enter the index of the element (0 to 9): 
Invalid index. Please enter a value between 0 and 9.
Please enter the index of the element (0 to 9): 
11
```
<!-- SAMPLES_END -->

範例說明：-1 無效，程式印錯誤後再提示；索引5對應11。

## 解法與核心程式

用迴圈初始化 values[i]=1+2i。先驗證索引再存取 values[index]，避免越界；文字錯誤清除串流狀態與該行，其後重試。固定十元素，時間與空間均 O(1)，重試次數由輸入決定。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
int values[10];
    for (int i = 0; i < 10; ++i) values[i] = 1 + 2 * i;
```

## 講義內容與重建補定

講義已知：講義給出十個奇數、0-based index、初始化陣列迴圈與精確的提示／非法索引字串。

自行補定：最後直接印元素、文字輸入恢復、EOF 終止由重建版補定，避免提示片段在串流失敗時不停止。

## 完整題解程式

完整可編譯版本：[../lab9_1.cpp](../lab9_1.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P1130295: use an actual ten-element odd-number array.
#include <iostream>
#include <limits>
using namespace std;
int main() {
    int values[10];
    for (int i = 0; i < 10; ++i) values[i] = 1 + 2 * i;
    int index;
    while (true) {
        cout << "Please enter the index of the element (0 to 9): \n";
        if (!(cin >> index)) {
            if (cin.eof()) return 0;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (index >= 0 && index < 10) break;
        cout << "Invalid index. Please enter a value between 0 and 9.\n";
    }
    cout << values[index] << '\n';
}
```
<!-- SOLUTION_CODE_END -->
