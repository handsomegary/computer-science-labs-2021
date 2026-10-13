# 2021 期中考 A：雞兔同籠

依提供的考卷與參考程式整理。題目採正式考卷，輸出字串以範例為準；必要的矛盾處理與補充行為於文末明列。

## 題目

農場籠中共有 x 個頭、y 條腿。每隻雞一個頭兩條腿，每隻兔子一個頭四條腿。計算雞與兔的數量；無非負整數解時輸出 no。反覆處理資料，直到讀到 0 0。

## 輸入格式

多組資料，每組依序輸入兩個整數 x、y，分別為頭數、腿數，以空白或換行分隔。0 0 是終止記號，不是要輸出的動物組合。

## 輸出格式

不印任何輸入提示。每組有解印 `Chick C Rabbit R` 與換行，其中 C、R 是雞、兔數；無解印小寫 `no` 與換行。讀到 0 0 印 `Bye` 與換行後結束。

## 限制與邊界

0 <= x,y <= 2147483647。雞、兔數必須為非負整數。除終止記號外，頭數或腿數為零仍照正常規則判定，例如 0 1 無解。使用 64 位中間計算，避免 2x、4x 在 32 位整數中溢位。考卷不要求範圍外輸入防呆；本實作對範圍外數值在 stderr 印 `Invalid input.` 與換行並回傳 1，EOF 正常結束。

## 解法說明

設雞數 C、兔數 R，C+R=x、2C+4R=y，因此 R=(y−2x)/2、C=x−R。合法條件為 y 是偶數且 2x <= y <= 4x。檢查條件後直接代入，不需要枚舉動物數量。每組時間 O(1)、額外空間 O(1)。

## 考卷依據與採用規則

依提供的考卷與參考程式：兩輸入順序、動物頭腿數、合法範圍、多組處理與終止記號採考卷；精確字串與大小寫採範例。以 64 位中間值是避免溢位的實作修正，沒有改變合法資料答案。

## 範例

範例 1 的 5 個頭、16 條腿得到雞 2、兔 3；15 條腿是奇數，無解。範例 2 檢查大數乘法與零邊界：1073741823 隻雞共有 2147483646 條腿；0 個頭、1 條腿無解。

以下是實跑的完整 stdout，不含終端機輸入回顯；範例獨立啟動程序，包含每個空格與換行。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
5
16
5
15
0
0
```

### 範例 1 輸出

```text
Chick 2 Rabbit 3
no
Bye
```

### 範例 2 輸入

```text
1073741823 2147483646
0 1
0 0
```

### 範例 2 輸出

```text
Chick 1073741823 Rabbit 0
no
Bye
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為本題解核心節錄，完整可編譯程式列於下一節。

```cpp
if (legs % 2 != 0 || legs < 2 * heads || legs > 4 * heads) {
    std::cout << "no\n";
} else {
    const long long rabbits = (legs - 2 * heads) / 2;
    const long long chicks = heads - rabbits;
    std::cout << "Chick " << chicks << " Rabbit " << rabbits << '\n';
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// Based on the provided exam and reference code.
#include <iostream>

int main()
{
    long long heads = 0;
    long long legs = 0;
    while (std::cin >> heads >> legs) {
        if (heads == 0 && legs == 0) {
            std::cout << "Bye\n";
            return 0;
        }
        if (heads < 0 || heads > 2147483647LL || legs < 0 || legs > 2147483647LL) {
            std::cerr << "Invalid input.\n";
            return 1;
        }
        if (legs % 2 != 0 || legs < 2 * heads || legs > 4 * heads) {
            std::cout << "no\n";
        } else {
            const long long rabbits = (legs - 2 * heads) / 2;
            const long long chicks = heads - rabbits;
            std::cout << "Chick " << chicks << " Rabbit " << rabbits << '\n';
        }
    }
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `exams/2021/midterm` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic problem_a.cpp -o problem_a
./problem_a
```

Windows PowerShell 執行 `./problem_a.exe`。獨立原始碼：[problem_a.cpp](../problem_a.cpp)。範例亦保存在本目錄的 `samples.json`。
