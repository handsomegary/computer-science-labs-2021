# 2024 Lab 9.4　P113032：局部二進位模式 LBP

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

給定灰階影像，對有完整3×3鄰域的每個內部像素，以中央值為門檻。鄰點值大於或等於中央值時，該位設1；否則設0。重建版採row-major位元順序：左上、上、右上、左、右、左下、下、右下依序為bit0–7。影像邊界沒有完整鄰域，結果設0。

## 輸入

先輸入列數 rows 與欄數 columns，再依列輸入 rows×columns 個0–255整數像素。若某像素不合法，清除當行後重新輸入整張影像。小於3×3的維度不需继續提供像素。

## 輸出

先印維度提示與矩陣提示。結果先印 `LBP Matrix:`，再印 rows 行、每行 columns 個代碼，每個代碼使用setw(5)右對齊。任一維度小於3時印 `The size of the matrix must be at least 3x3 to compute LBP.`；非法像素印 `Invalid input detected! Matrix values must be between 0 and 255.` 後重試。非正／超解析上限／配置失敗印error。

## 限制

重建基本影像：3≤rows,columns≤1000，像素0≤v≤255。小維度可作錯誤處理測試。程式解析維度上限為2147483647，乘積另受size_t與配置限制。必須使用陣列儲存原影像與結果，代碼範圍0–255。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
3 3
90 110 90
110 100 90
110 90 110
```

### 範例 1 輸出

```text
Please enter the number of rows and columns: Please input the grayscale image matrix (each element should be an integer between 0 and 255):
LBP Matrix:
    0    0    0
    0  170    0
    0    0    0
```
<!-- SAMPLES_END -->

範例說明：中央100只有上、左、左下、右下達到門檻，代碼為2¹+2³+2⁵+2⁷=170；八個邊界像素都印0。

## 解法與核心程式

配置兩個扁平陣列，以row×columns+col映射二維座標，結果先清0。只掃內部位置，依鄰點row-major順序逐位比較並 OR 到代碼。兩個維度都需≥3，避免圖片只檢查rows時發生窄矩陣越界。時間與空間O(rows×columns)。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
for (long long row = 1; row < rows - 1; ++row) {
        for (long long col = 1; col < columns - 1; ++col) {
            const size_t position = static_cast<size_t>(row * columns + col);
            unsigned bit = 0;
            for (int dr = -1; dr <= 1; ++dr)
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    const size_t neighbor = static_cast<size_t>((row + dr) * columns + col + dc);
                    if (image[neighbor] >= image[position]) lbp[position] |= 1 << bit;
                    ++bit;
                }
        }
    }
```

## 講義內容與重建補定

講義已知：講義給出≥門檻設1、3×3鄰域、灰階0–255、setw(5)與英文提示。第17張圖雖有遮蓋，仍能讀到左bit3、左下bit5、下bit6。

自行補定：其他五個位依row-major補齊、邊界0、維度提示、兩維都至少3、完整尺寸限制、輸入錯誤恢復均為重建版補定，五個被遮住的指派不冒稱教授原碼。

## 完整題解程式

完整可編譯版本：[../lab9_4.cpp](../lab9_4.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113032: row-major neighbor bits; boundary LBP codes stay zero.
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
using namespace std;

int main() {
    long long rows, columns;
    cout << "Please enter the number of rows and columns: ";
    if (!(cin >> rows >> columns) || rows < 1 || columns < 1 ||
        rows > 2147483647LL || columns > 2147483647LL) { cout << "error\n"; return 1; }
    if (rows < 3 || columns < 3) {
        cout << "The size of the matrix must be at least 3x3 to compute LBP.\n";
        return 0;
    }
    if (static_cast<unsigned long long>(rows) > numeric_limits<size_t>::max() / static_cast<unsigned long long>(columns)) {
        cout << "error\n";
        return 1;
    }
    const size_t count = static_cast<size_t>(rows) * static_cast<size_t>(columns);
    unique_ptr<int[]> image, lbp;
    try { image.reset(new int[count]); lbp.reset(new int[count]()); }
    catch (const bad_alloc &) { cout << "error\n"; return 1; }
    while (true) {
        cout << "Please input the grayscale image matrix (each element should be an integer between 0 and 255):\n";
        bool valid = true;
        for (size_t i = 0; i < count; ++i) {
            if (!(cin >> image[i]) || image[i] < 0 || image[i] > 255) { valid = false; break; }
        }
        if (valid) break;
        if (cin.eof()) return 0;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input detected! Matrix values must be between 0 and 255.\n";
    }
    for (long long row = 1; row < rows - 1; ++row) {
        for (long long col = 1; col < columns - 1; ++col) {
            const size_t position = static_cast<size_t>(row * columns + col);
            unsigned bit = 0;
            for (int dr = -1; dr <= 1; ++dr)
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    const size_t neighbor = static_cast<size_t>((row + dr) * columns + col + dc);
                    if (image[neighbor] >= image[position]) lbp[position] |= 1 << bit;
                    ++bit;
                }
        }
    }
    cout << "LBP Matrix:\n";
    for (long long row = 0; row < rows; ++row) {
        for (long long col = 0; col < columns; ++col)
            cout << setw(5) << lbp[static_cast<size_t>(row * columns + col)];
        cout << '\n';
    }
}
```
<!-- SOLUTION_CODE_END -->
