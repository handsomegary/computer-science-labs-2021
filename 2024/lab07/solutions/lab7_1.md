# 2024 Lab 7.1　P113025：三角形周長與面積

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

給定三個整數邊長，先檢查是否能構成三角形。可以時分別呼叫周長與面積函式輸出結果；不能時輸出 error。必須使用兩個函式，不得把全部計算只寫在 `main`。

## 輸入

一筆資料，三個邊長 x、y、z，以空白或換行分隔。

## 輸出

可構成三角形時輸出兩行：`perimeter: P`、`area: A`。P 為整數；A 採 C++ 預設浮點格式、最多六位有效數字。無效或無法讀取的邊長只印 `error`，最後換行；不重新要求輸入。

## 限制

合法邊長在 1–2147483647，且任意兩邊相加大於第三邊。0、負數、超範圍與退化三角形屬錯誤處理案例。使用 `void trianglePerimeter(...)` 與 `void triangleArea(...)`。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
3 4 5
```

### 範例 1 輸出

```text
perimeter: 12
area: 6
```
<!-- SAMPLES_END -->

範例說明：3、4、5 的周長為 12，s=6，面積為 sqrt(6×3×2×1)=6。

## 解法與核心程式

以 64 位元整數檢查三角不等式並加總周長。Heron 公式 s=(x+y+z)/2、A=sqrt(s(s-x)(s-y)(s-z)) 的 s 必須採浮點除法；圖片中的整數除二會把 1、1、1 的半周長截斷。時間、額外空間均 O(1)。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
void triangleArea(long long x, long long y, long long z) {
    const long double s = (static_cast<long double>(x) + y + z) / 2;
    cout << "area: " << setprecision(6) << sqrt(s * (s-x) * (s-y) * (s-z)) << '\n';
}
```

## 講義內容與重建補定

講義已知：講義指定兩個函式、三角形防呆、`error`、周長相加與 Heron 公式，圖片給出 `perimeter:`、`area:` 標籤。

自行補定：單筆處理、正 `int` 邊長範圍、六位有效數字、超範圍與讀取錯誤行為由重建版補定；修正圖片整數半周長與加總溢位。

## 完整題解程式

完整可編譯版本：[../lab7_1.cpp](../lab7_1.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113025: use two functions, without truncating Heron's semiperimeter.
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

void trianglePerimeter(long long x, long long y, long long z) {
    cout << "perimeter: " << x + y + z << '\n';
}
void triangleArea(long long x, long long y, long long z) {
    const long double s = (static_cast<long double>(x) + y + z) / 2;
    cout << "area: " << setprecision(6) << sqrt(s * (s-x) * (s-y) * (s-z)) << '\n';
}
int main() {
    long long x, y, z;
    if (!(cin >> x >> y >> z) || x < 1 || y < 1 || z < 1 || x > 2147483647LL ||
        y > 2147483647LL || z > 2147483647LL || x + y <= z || x + z <= y || y + z <= x) {
        cout << "error\n";
        return 0;
    }
    trianglePerimeter(x, y, z);
    triangleArea(x, y, z);
}
```
<!-- SOLUTION_CODE_END -->
