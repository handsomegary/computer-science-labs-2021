# 2021 期中考 E：極值平均與十進位／八進位／二進位

依提供的考卷與參考程式整理。題目採正式考卷，輸出字串以範例為準；必要的矛盾處理與補充行為於文末明列。

## 題目

取得 n 筆非負收入資料，以最大值與最小值的平均代表整組資料。若平均不是整數，要求重新輸入一整組：包括新的 n 與新的全部收入。合法平均依序印十進位、八進位與二進位；若平均至少為二進位 111111，印富裕訊息，否則印鼓勵訊息。

## 輸入格式

先輸入筆數 n，接著 n 個收入整數。若須重試，再從新 n 開始提供資料；n 可以與上一組不同。數值以空白或換行分隔。取得第一組整數平均後結束。

## 輸出格式

不印輸入提示。平均非整數時印 `Input again!` 與換行。最後依序四行：`Decimal A`、`Octet O`、`Binary B`，第四行為 `The country is rich` 或 `Come on`；各行最後換行。O、B 不加前綴或前導零，平均0時兩者都印0。

## 限制與邊界

正常資料1 <= n <= 2147483647，收入值0–2147483647。考卷一面稱n為正整數，一面把n的數值範圍列為含0；由於空資料沒有最大與最小值，本實作 n=0 印 Input again! 並重新讀n。二進位111111的數值是63，所以判斷平均>=63，不是與十進位111111或字串比較。極值相加使用64位，避免兩個INTMAX相加溢位。範圍外筆數／收入在stderr分別印 `Invalid data count.`／`Invalid revenue data.` 與換行並回傳1；尚未輸入n時EOF正常結束。

## 解法說明

串流讀n個值，只維持minimum、maximum，沒有配置n個元素的陣列。sum=minimum+maximum為奇數時，平均非整數，重讀整組。偶數時A=sum/2，以oct輸出八進位並恢復dec，二進位用遞迴先印商再印餘數。每組時間O(n)，極值計算空間O(1)，二進位列印堆疊O(log(A+1))。

## 考卷依據與採用規則

依提供的考卷與參考程式：只平均極值、平均非整數重輸、三種進位、富裕門檻採考卷。重試範例從n=3變n=4，因此明確必須重讀n與完整資料，不能只重讀前一次n筆。n=0的處理是解決空資料矛盾的補充規則；Octet 字串保留原sample拼法。

## 範例

範例1首先最小10、最大21，平均15.5，因此重讀一組4筆；新組最小10、最大30，平均20，八進位24、二進位10100，未達63。範例2恰為門檻63，二進位111111，判為rich。範例3檢查收入全0。

以下是實跑的完整 stdout，不含終端機輸入回顯；範例獨立啟動程序，包含每個空格與換行。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
3
10
15
21
4
23
10
12
30
```

### 範例 1 輸出

```text
Input again!
Decimal 20
Octet 24
Binary 10100
Come on
```

### 範例 2 輸入

```text
1
63
```

### 範例 2 輸出

```text
Decimal 63
Octet 77
Binary 111111
The country is rich
```

### 範例 3 輸入

```text
2
0
0
```

### 範例 3 輸出

```text
Decimal 0
Octet 0
Binary 0
Come on
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為本題解核心節錄，完整可編譯程式列於下一節。

```cpp
const long long sum = minimum + maximum;
if (sum % 2 != 0) {
    std::cout << "Input again!\n";
    continue;
}
const unsigned average = static_cast<unsigned>(sum / 2);
std::cout << "Decimal " << average << "\nOctet " << std::oct << average
          << std::dec << "\nBinary ";
printBinary(average);
std::cout << '\n' << (average >= 63 ? "The country is rich\n" : "Come on\n");
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// Based on the provided exam and reference code.
#include <algorithm>
#include <iostream>

void printBinary(unsigned number)
{
    if (number >= 2) printBinary(number / 2);
    std::cout << number % 2;
}

int main()
{
    long long count = 0;
    while (std::cin >> count) {
        if (count < 0 || count > 2147483647LL) {
            std::cerr << "Invalid data count.\n";
            return 1;
        }
        // The description requires a positive count; an empty data set has no extrema.
        if (count == 0) {
            std::cout << "Input again!\n";
            continue;
        }
        long long minimum = 2147483647LL;
        long long maximum = 0;
        for (long long index = 0; index < count; ++index) {
            long long value = 0;
            if (!(std::cin >> value) || value < 0 || value > 2147483647LL) {
                std::cerr << "Invalid revenue data.\n";
                return 1;
            }
            minimum = std::min(minimum, value);
            maximum = std::max(maximum, value);
        }
        const long long sum = minimum + maximum;
        if (sum % 2 != 0) {
            std::cout << "Input again!\n";
            continue; // Read both the new count and a complete new set of values.
        }
        const unsigned average = static_cast<unsigned>(sum / 2);
        std::cout << "Decimal " << average << "\nOctet " << std::oct << average << std::dec << "\nBinary ";
        printBinary(average);
        std::cout << '\n' << (average >= 63 ? "The country is rich\n" : "Come on\n");
        return 0;
    }
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `exams/2021/midterm` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic problem_e.cpp -o problem_e
./problem_e
```

Windows PowerShell 執行 `./problem_e.exe`。獨立原始碼：[problem_e.cpp](../problem_e.cpp)。範例亦保存在本目錄的 `samples.json`。
