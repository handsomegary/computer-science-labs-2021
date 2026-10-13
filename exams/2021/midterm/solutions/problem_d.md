# 2021 期中考 D：區間內的 Armstrong Numbers

依提供的考卷與參考程式整理。題目採正式考卷，輸出字串以範例為準；必要的矛盾處理與補充行為於文末明列。

## 題目

若一個非負整數等於其每位數字的「位數次方」總和，就稱為 Armstrong number。例如 407=4^3+0^3+7^3、1634=1^4+6^4+3^4+4^4。找出閉區間 [a,b] 的全部 Armstrong numbers，依小到大輸出；無解輸出 none。

## 輸入格式

依序輸入整數下界 a、上界 b，以空白或換行分隔。

## 輸出格式

不印任何輸入提示。有解時以 ` & ` 分隔數值，依範例在最後一個數值後保留一個空格，再換行，例如 `153 & 370 & 371 & 407 `。沒有答案時印 `none` 與換行，不加尾端空格。

## 限制與邊界

0 <= a,b <= 2147483647。0 視為一位數，所以 0 也是 Armstrong number；所有 0–9 都符合。兩界包含在查找區間中。上界最多十位；不得從 a 到 b 線性掃描。若 a>b，視為空區間，輸出 none；考卷不要求這種逆序防呆，此為明確的補充規則。範圍外數值在 stderr 印 `Invalid range.` 與換行並回傳 1。

## 解法說明

答案只取決於各數字出現幾次。針對每種位數 L=1..10，枚舉 c0+...+c9=L 的數位多重集合，算 S=Σcd×d^L。只有 S 位數等於 L、數位出現次數也恰好是該集合且在區間內時，才是答案；排序後印出。

L位多重集合數為 C(L+9,9)，L=1..10合計184755種。每次以整數乘法計次方，用64位中間值；最大總和10×9^10仍可安全表示。時間由數位集合總數決定，而非區間寬度；額外空間為遞迴深度及答案列表。

## 考卷依據與採用規則

依提供的考卷與參考程式：Armstrong 定義、閉區間、輸入範圍與 none 採考卷。分隔符與最後空格採 sample。文字稱正整數邊界，但數值範圍含0，因此接受0。數位集合搜尋是效率修訂，不以硬編碼答案清單替代計算。

## 範例

範例 1 的 100–999 有 153、370、371、407。範例 2 的 10–99 無答案。範例 3 包含下界0，十個一位數都等於自己的一次方。

以下是實跑的完整 stdout，不含終端機輸入回顯；範例獨立啟動程序，包含每個空格與換行。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
100
999
```

### 範例 1 輸出

```text
153 & 370 & 371 & 407 
```

### 範例 2 輸入

```text
10
99
```

### 範例 2 輸出

```text
none
```

### 範例 3 輸入

```text
0 9
```

### 範例 3 輸出

```text
0 & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & 9 
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為本題解核心節錄，完整可編譯程式列於下一節。

```cpp
if (digit == 9) {
    counts[9] = remaining;
    const long long candidate = sum + remaining * powers[9];
    if (candidate >= lower && candidate <= upper && matchingDigits(candidate, length, counts))
        answers.push_back(candidate);
    return;
}
for (int count = 0; count <= remaining; ++count) {
    const long long nextSum = sum + count * powers[digit];
    if (nextSum > upper) break;
    counts[digit] = count;
    enumerateDigits(digit + 1, remaining - count, length, nextSum,
                    powers, counts, lower, upper, answers);
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// Based on the provided exam and reference code.
// Enumerate digit multisets rather than scanning the requested integer range.
#include <algorithm>
#include <iostream>
#include <vector>

bool matchingDigits(long long number, int length, const int counts[10])
{
    int actual[10] = {};
    int digits = 0;
    do {
        ++actual[number % 10];
        ++digits;
        number /= 10;
    } while (number > 0);
    if (digits != length) return false;
    for (int digit = 0; digit < 10; ++digit)
        if (actual[digit] != counts[digit]) return false;
    return true;
}

void enumerateDigits(int digit, int remaining, int length, long long sum,
                     const long long powers[10], int counts[10],
                     long long lower, long long upper, std::vector<long long>& answers)
{
    if (digit == 9) {
        counts[9] = remaining;
        const long long candidate = sum + remaining * powers[9];
        if (candidate >= lower && candidate <= upper && matchingDigits(candidate, length, counts))
            answers.push_back(candidate);
        return;
    }
    for (int count = 0; count <= remaining; ++count) {
        const long long nextSum = sum + count * powers[digit];
        if (nextSum > upper) break;
        counts[digit] = count;
        enumerateDigits(digit + 1, remaining - count, length, nextSum,
                        powers, counts, lower, upper, answers);
    }
}

int main()
{
    long long lower = 0, upper = 0;
    if (!(std::cin >> lower >> upper) || lower < 0 || upper < 0
        || lower > 2147483647LL || upper > 2147483647LL) {
        std::cerr << "Invalid range.\n";
        return 1;
    }
    std::vector<long long> answers;
    int maximumLength = 1;
    for (long long rest = upper; rest >= 10; rest /= 10) ++maximumLength;
    if (lower <= upper) {
        for (int length = 1; length <= maximumLength; ++length) {
            long long powers[10] = {};
            for (int digit = 0; digit < 10; ++digit) {
                powers[digit] = 1;
                for (int exponent = 0; exponent < length; ++exponent) powers[digit] *= digit;
            }
            int counts[10] = {};
            enumerateDigits(0, length, length, 0, powers, counts, lower, upper, answers);
        }
    }
    std::sort(answers.begin(), answers.end());
    answers.erase(std::unique(answers.begin(), answers.end()), answers.end());
    if (answers.empty()) {
        std::cout << "none\n";
    } else {
        for (std::size_t index = 0; index < answers.size(); ++index) {
            if (index != 0) std::cout << " & ";
            std::cout << answers[index];
        }
        std::cout << " \n"; // The exam sample includes a space after the last value.
    }
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `exams/2021/midterm` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic problem_d.cpp -o problem_d
./problem_d
```

Windows PowerShell 執行 `./problem_d.exe`。獨立原始碼：[problem_d.cpp](../problem_d.cpp)。範例亦保存在本目錄的 `samples.json`。
