# 2024 Lab 9.2　P113030：指定區間總和

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

輸入陣列大小與各浮點元素，再選擇含兩端的索引區間。每個元素先四捨五入為一位小數（恰好一半時遠離零），存成十分位整數，再累加所選區間。講義題名雖為 Maximum Path Sum，本重建題意是指定區間總和，不是搜尋最大子陣列。

## 輸入

依序輸入正整數 n、n 個浮點元素、整數 start 和 end。大小不合法則重輸入大小；元素不合法則重輸入整組元素；區間不合法則重輸入區間。重試資料以新行提交，EOF 結束。

## 輸出

依序有大小、元素、區間提示。最終印 `The sum of the values in the index range [start, end] is: V`，V 固定一位小數。非法大小／元素／區間會印 `Wrong Input! Please enter again:` 後重試；配置失败或總和超出 64 位元整數時印 error。提示的精確換行以範例與完整程式為準。

## 限制

重建基本測資：1≤n≤100000；元素為有限浮點數，-2147483648≤value≤2147483647；0≤start≤end<n。四捨五入後的十分位總和必須可由帶符號64位元存放。程式可解析 n≤2147483647，但受記憶體與輸出時間限制。必須以陣列存每個元素。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
10
-1.5 -3.5 3.0 -2.4 -1.8 -3.0 4.5 5.7 -8.9 3.4
2 5
```

### 範例 1 輸出

```text
Please enter the size of the array: Please enter the elements of the array:
Please enter two integers, start and end, representing the selected index range: The sum of the values in the index range [2, 5] is: -4.2
```
<!-- SAMPLES_END -->

範例說明：索引2至5的元素為3.0、-2.4、-1.8、-3.0，總和-4.2。

## 解法與核心程式

每個輸入乘 10 並 round 到整數後存入陣列。對 [start,end] 累加，加入前先檢查帶符號加法溢位。輸出時以絕對值整除 10 與餘數分別印整數、小數，不把大總和轉回浮點而丟掉最後一位；也能正確印 -0.1。時間 O(n)、空間 O(n)。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
long long sum = 0;
    for (long long i = start; i <= end; ++i) {
        const long long value = values[static_cast<size_t>(i)];
        if ((value > 0 && sum > numeric_limits<long long>::max() - value) ||
            (value < 0 && sum < numeric_limits<long long>::min() - value)) {
            cout << "error\n";
            return 1;
        }
        sum += value;
    }
```

## 講義內容與重建補定

講義已知：講義給出 n、浮點元素、含端點的索引範圍、十分位取整、大小／元素／區間驗證與最終英文標籤。

自行補定：基本 n 上限、大小提示、EOF 與文字恢復、64 位元溢位檢查及精確整數輸出為重建版補定／改善。捨入使用現有 C++ long double 的 round，不另引入精確十進位解析器。

## 完整題解程式

完整可編譯版本：[../lab9_2.cpp](../lab9_2.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113030: sum the inclusive range, after rounding each input to tenths.
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
using namespace std;

bool recoverInput() {
    if (cin.eof()) return false;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}
int main() {
    long long size;
    while (true) {
        cout << "Please enter the size of the array: ";
        if ((cin >> size) && size >= 1 && size <= 2147483647LL) break;
        if (!recoverInput()) return 0;
        cout << "Wrong Input! Please enter again:\n";
    }
    unique_ptr<long long[]> values;
    try { values.reset(new long long[static_cast<size_t>(size)]); }
    catch (const bad_alloc &) { cout << "error\n"; return 1; }
    while (true) {
        cout << "Please enter the elements of the array:\n";
        bool valid = true;
        for (long long i = 0; i < size; ++i) {
            long double value;
            if (!(cin >> value) || !isfinite(value) || value < -2147483648.0L || value > 2147483647.0L) {
                valid = false;
                break;
            }
            values[static_cast<size_t>(i)] = static_cast<long long>(round(value * 10));
        }
        if (valid) break;
        if (!recoverInput()) return 0;
        cout << "Wrong Input! Please enter again:\n";
    }
    long long start, end;
    while (true) {
        cout << "Please enter two integers, start and end, representing the selected index range: ";
        if ((cin >> start >> end) && start >= 0 && start <= end && end < size) break;
        if (!recoverInput()) return 0;
        cout << "Wrong Input! Please enter again:\n";
    }
    long long sum = 0;
    for (long long i = start; i <= end; ++i) {
        const long long value = values[static_cast<size_t>(i)];
        if ((value > 0 && sum > numeric_limits<long long>::max() - value) ||
            (value < 0 && sum < numeric_limits<long long>::min() - value)) {
            cout << "error\n";
            return 1;
        }
        sum += value;
    }
    const unsigned long long magnitude = sum < 0 ? static_cast<unsigned long long>(-(sum + 1)) + 1
                                                 : static_cast<unsigned long long>(sum);
    cout << "The sum of the values in the index range [" << start << ", " << end << "] is: ";
    if (sum < 0) cout << '-';
    cout << magnitude / 10 << '.' << magnitude % 10 << '\n';
}
```
<!-- SOLUTION_CODE_END -->
