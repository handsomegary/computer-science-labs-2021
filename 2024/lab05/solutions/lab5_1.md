# 2024 Lab 5.1：Calculator：整數加減乘與次方

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

持續接收 +、−、*、^ 與 e 字元，其中 ^ 表示非負整數次方，不是 XOR。四個運算符各取得兩個非負整數 a、b，印結果；e 結束。使用 switch 分派。結果採有號 64 位整數，次方超出範圍時印錯誤後繼續。

## 輸入格式

一連串字元與數值。遇到 +、-、*、^ 時依序再讀 a、b；e 不讀運算元而結束。運算符之間的空白、Tab、CR、LF 忽略。其他字元各自印錯誤，不讀運算元。

## 輸出格式

開始印 `Welcome to use our calculator. Type 'e' to exit.` 與換行。每個有效運算符印不換行的 `Enter a and b: `。合法運算後印 `Calculation result: a OP b = R` 以及兩個換行；OP 是原運算符。

非法運算符印 `Incorrect mathematical operator entered. Enter a new one.` 與換行。非法運算元重試時印 `Wrong numbers. Enter two integers again.` 與換行；不重印 Enter a and b。次方溢位印 `Calculation result is out of range.` 與兩個換行。e 印 `Goodbye~` 與換行，EOF 不印告別詞。文字造成運算元讀取失敗時清除該行。

## 限制與邊界

0 <= a,b <= 2147483647；R 的正常範圍為 −9223372036854775808 至 9223372036854775807。a−b 可以為負，最大加法和乘法必須先轉 long long 再算。^ 的指數 b 可以為 0；本題定義 0^0 = 1。

## 解法說明

以 cin.get 讀字元、switch 選運算。加減乘先擴充整數型態；次方使用既有修訂的平方乘冪，每次需要相乘前以 max/factor 檢查溢位，O(log(b+1)) 即可處理很大的指數。額外空間 O(1)。

## 講義可確認的規則

Review P113017 給 +、-、*、^、e、32 位非負運算元、switch、cin.get 忽略空白、先 static_cast 再乘、歡迎／結果／告別與錯誤運算符字串。原次方迴圈的初始值為 1。

## 重建版自行補定的規則

0^0=1、次方結果溢位診斷、非法運算元重試與 EOF 行為以上述規格為準。快速冪是 repository 修訂題解，取代線性次方迴圈。

## 範例與說明

範例 1 計算 2+3=5 與 2^3=8 後退出。範例 2 最大運算元相乘仍在 long long 範圍，得到 4611686014132420609；2^63 超出正上界，改印溢位訊息後仍可輸入 e。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
+
2 3
^
2 3
e
```

### 範例 1 輸出

```text
Welcome to use our calculator. Type 'e' to exit.
Enter a and b: Calculation result: a + b = 5

Enter a and b: Calculation result: a ^ b = 8

Goodbye~
```

### 範例 2 輸入

```text
*
2147483647 2147483647
^
2 63
e
```

### 範例 2 輸出

```text
Welcome to use our calculator. Type 'e' to exit.
Enter a and b: Calculation result: a * b = 4611686014132420609

Enter a and b: Calculation result is out of range.

Goodbye~
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
while (exponent > 0) {
    if (exponent % 2 != 0) {
        if (factor != 0 && result > std::numeric_limits<long long>::max() / factor) return false;
        result *= factor;
    }
    exponent /= 2;
    if (exponent > 0) {
        if (factor != 0 && factor > std::numeric_limits<long long>::max() / factor) return false;
        factor *= factor;
    }
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
#include <iostream>
#include <limits>

bool readOperands(int& first, int& second)
{
    std::cout << "Enter a and b: ";
    while (true) {
        if (std::cin >> first >> second) {
            if (first >= 0 && second >= 0) return true;
        } else {
            if (std::cin.eof()) return false;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Wrong numbers. Enter two integers again.\n";
    }
}

bool integerPower(int base, int exponent, long long& result)
{
    result = 1; // The Review's initial value also defines 0^0 as 1.
    long long factor = base;
    while (exponent > 0) {
        if (exponent % 2 != 0) {
            if (factor != 0 && result > std::numeric_limits<long long>::max() / factor) return false;
            result *= factor;
        }
        exponent /= 2;
        if (exponent > 0) {
            if (factor != 0 && factor > std::numeric_limits<long long>::max() / factor) return false;
            factor *= factor;
        }
    }
    return true;
}

int main()
{
    std::cout << "Welcome to use our calculator. Type 'e' to exit.\n";
    char operation = 0;
    while (std::cin.get(operation)) {
        int first = 0;
        int second = 0;
        long long result = 0;
        switch (operation) {
        case 'e':
            std::cout << "Goodbye~\n";
            return 0;
        case '+': case '-': case '*': case '^':
            if (!readOperands(first, second)) return 0;
            switch (operation) {
            case '+': result = static_cast<long long>(first) + second; break;
            case '-': result = static_cast<long long>(first) - second; break;
            case '*': result = static_cast<long long>(first) * second; break;
            case '^':
                if (!integerPower(first, second, result)) {
                    std::cout << "Calculation result is out of range.\n\n";
                    continue;
                }
                break;
            }
            std::cout << "Calculation result: a " << operation << " b = " << result << "\n\n";
            break;
        case '\n': case '\r': case '\t': case ' ':
            break;
        default:
            std::cout << "Incorrect mathematical operator entered. Enter a new one.\n";
            break;
        }
    }
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab05` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab5_1.cpp -o lab5_1
./lab5_1
```

Windows PowerShell 執行 `./lab5_1.exe`。完整原始碼為 [`lab5_1.cpp`](../lab5_1.cpp)；機器可驗證範例在本目錄 `samples.json`。
