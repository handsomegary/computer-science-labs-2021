# 2021 期中考 B：逐次數位加總

依提供的考卷與參考程式整理。題目採正式考卷，輸出字串以範例為準；必要的矛盾處理與補充行為於文末明列。

## 題目

令 f(n) 為 n 的十進位各位數總和。反覆求 f，直到結果只剩一位數；列出每一次實際運算與最後的 summing digit。輸入值超出範圍時先印錯誤訊息，再重新取得一個值。

## 輸入格式

輸入一個整數 n；若該值不在合法範圍，繼續輸入替代值，直到取得合法 n。數值以空白或換行分隔。接受一個合法 n 並完成計算後，程式結束，不再處理下一筆。

## 輸出格式

不印輸入提示。每個範圍錯誤印 `You should input a positive integer` 與換行。第一次加總格式為 `f(n)=d1+d2+...+dm=S`，下一次為 `f(f(n))=...`，依次增加外層 f；等號與加號前後沒有空白，每行最後換行。位數由左至右輸出，包含 0。最後印 `The summing digit is:G` 與換行，冒號後沒有空白。若輸入本身是單一位數，只印最後一行，沒有加總運算行。

## 限制與邊界

0 <= n <= 2147483647。考卷文字稱正整數，但明列範圍包含 0；本實作以該範圍為準，n=0 合法且最後數字為 0。逐一讀取空白分隔的數值 token；非法 token、負數或超大數值都印同一錯誤訊息並取得下一個 token。可接受開頭的加號、前導零與數值為零的負零表示。即使超大數字位於 EOF 前且沒有換行，也先印錯誤，再因無新輸入而正常結束。用整數除法取得數位，不使用浮點 pow。

## 解法說明

當 n>=10，找最高十進位除數，從最左位依序取得 n/divisor%10、印出數位並累加，再以總和取代 n。iteration 決定外層 f 的數量，所以不省略中間步驟。首輪最多十位，後續更短；時間為所有實際處理位數總和，額外數值空間 O(1)。

## 考卷依據與採用規則

依提供的考卷與參考程式：逐次加總目的、輸入範圍、範圍外重試採考卷，f 的巢狀形式與所有字串採範例。範圍含 0 與「positive」用詞不一致時採明列範圍；單位數不用執行 f，直接報告結果。

## 範例

範例 1 先拒絕 −5，再由 1234567892 算出 47、11、2，三個加總行都必須保留。範例 2 的 100 仍要印出兩個零；範例 3 確認範圍下界 0。

以下是實跑的完整 stdout，不含終端機輸入回顯；範例獨立啟動程序，包含每個空格與換行。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
-5
1234567892
```

### 範例 1 輸出

```text
You should input a positive integer
f(n)=1+2+3+4+5+6+7+8+9+2=47
f(f(n))=4+7=11
f(f(f(n)))=1+1=2
The summing digit is:2
```

### 範例 2 輸入

```text
100
```

### 範例 2 輸出

```text
f(n)=1+0+0=1
The summing digit is:1
```

### 範例 3 輸入

```text
0
```

### 範例 3 輸出

```text
The summing digit is:0
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為本題解核心節錄，完整可編譯程式列於下一節。

```cpp
long long sum = 0;
while (divisor > 0) {
    const long long digit = number / divisor % 10;
    std::cout << digit;
    sum += digit;
    divisor /= 10;
    if (divisor > 0) std::cout << '+';
}
std::cout << '=' << sum << '\n';
number = sum;
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// Based on the provided exam and reference code.
#include <iostream>
#include <string>

bool parseNumber(const std::string& token, long long& number)
{
    std::size_t position = 0;
    bool negative = false;
    if (!token.empty() && (token[0] == '+' || token[0] == '-')) {
        negative = token[0] == '-';
        position = 1;
    }
    if (position == token.size()) return false;
    long long value = 0;
    for (; position < token.size(); ++position) {
        if (token[position] < '0' || token[position] > '9') return false;
        const int digit = token[position] - '0';
        if (value > (2147483647LL - digit) / 10) return false;
        value = value * 10 + digit;
    }
    if (negative && value != 0) return false;
    number = value;
    return true;
}

int main()
{
    long long number = 0;
    std::string token;
    while (std::cin >> token) {
        if (parseNumber(token, number)) break;
        std::cout << "You should input a positive integer\n";
    }
    if (!std::cin || !parseNumber(token, number)) return 0;
    unsigned iteration = 0;
    while (number >= 10) {
        ++iteration;
        for (unsigned index = 0; index < iteration; ++index) std::cout << "f(";
        std::cout << 'n';
        for (unsigned index = 0; index < iteration; ++index) std::cout << ')';
        std::cout << '=';
        long long divisor = 1;
        for (long long rest = number; rest >= 10; rest /= 10) divisor *= 10;
        long long sum = 0;
        while (divisor > 0) {
            const long long digit = number / divisor % 10;
            std::cout << digit;
            sum += digit;
            divisor /= 10;
            if (divisor > 0) std::cout << '+';
        }
        std::cout << '=' << sum << '\n';
        number = sum;
    }
    std::cout << "The summing digit is:" << number << '\n';
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `exams/2021/midterm` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic problem_b.cpp -o problem_b
./problem_b
```

Windows PowerShell 執行 `./problem_b.exe`。獨立原始碼：[problem_b.cpp](../problem_b.cpp)。範例亦保存在本目錄的 `samples.json`。
