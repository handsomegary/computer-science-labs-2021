# 2024 Lab 3.4：Find the Bomb：逐步縮小猜測範圍

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

先輸入炸彈位置 T，再讓士兵猜測。上下界起初為 0、100，炸彈與每次有效猜測必須嚴格位於界內。猜得較低時更新下界，較高時更新上界；猜中後印炸彈位置及有效猜測次數。使用 while 與 if/else。

## 輸入格式

第一個整數為 T，其後為一連串整數猜測 G。錯誤的炸彈值或猜測值須重新輸入；不合法猜測不計入輪數。正常測資最後提供猜中 T 的值。

## 輸出格式

先印 `Enter the bomb number (0~100): `。每次有效猜測之前印 `Range L~U: `，例如 `Range 0~65: `。值不在目前開區間，或讀取失敗時印 `Out of range! Please enter again: ` 重新取得值；這三種提示末尾都有一個空格，沒有換行。

猜中後印 `Bomb number: T` 與換行，再印 `Rounds: K` 與換行。文字造成讀取錯誤時清除該行；EOF 直接回傳 0，不輸出假的結果。

## 限制與邊界

T 為 1–99；每次有效 G 滿足 L < G < U。輸入整數須能以 32 位 int 讀取。每次錯誤猜測都使區間縮小，因此有效猜測最多 99 輪。

## 解法說明

readWithin 用 while 重試，只有取得開區間內的值才回傳成功。主迴圈每成功取值才遞增 rounds，再以 if/else 更新界限或退出。因此重試不會改變界限與輪數。時間 O(有效猜測 + 重試)，額外空間 O(1)。

## 講義可確認的規則

Review 的 P113012 明確給定開區間 0–100、目標及範圍提示、越界提示，並提供 lower/upper 更新程式片段。

## 重建版自行補定的規則

最終結果用 Bomb number／Rounds 兩行；越界重試不計輪數；讀取錯誤與 EOF 的處理依上述介面。此重建格式取代先前未定義的最終句子。

## 範例與說明

範例 1 依序猜 65、30、50，區間由 0–100 縮為 0–65、30–65，共 3 輪。範例 2 的目標 0、100 與猜測 0 都被拒絕；目標 1 一次猜中，只計 1 輪。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
50
65
30
50
```

### 範例 1 輸出

```text
Enter the bomb number (0~100): Range 0~100: Range 0~65: Range 30~65: Bomb number: 50
Rounds: 3
```

### 範例 2 輸入

```text
0
100
1
0
1
```

### 範例 2 輸出

```text
Enter the bomb number (0~100): Out of range! Please enter again: Out of range! Please enter again: Range 0~100: Out of range! Please enter again: Bomb number: 1
Rounds: 1
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
++rounds;
if (guess == target) break;
else if (guess < target) lower = guess;
else upper = guess;
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
#include <iostream>
#include <limits>

bool readWithin(int& number, int lower, int upper)
{
    while (true) {
        if (std::cin >> number) {
            if (number > lower && number < upper) {
                return true;
            }
        } else {
            if (std::cin.eof()) {
                return false;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Out of range! Please enter again: ";
    }
}

int main()
{
    int target = 0;
    std::cout << "Enter the bomb number (0~100): ";
    if (!readWithin(target, 0, 100)) {
        return 0;
    }
    int lower = 0;
    int upper = 100;
    int guess = 0;
    int rounds = 0;
    while (true) {
        std::cout << "Range " << lower << '~' << upper << ": ";
        if (!readWithin(guess, lower, upper)) {
            return 0;
        }
        ++rounds; // Invalid input retries are not guesses.
        if (guess == target) {
            break;
        } else if (guess < target) {
            lower = guess;
        } else {
            upper = guess;
        }
    }
    // The Review requests these two values but omits their exact final wording.
    std::cout << "Bomb number: " << target << "\nRounds: " << rounds << '\n';
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab03` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab3_4.cpp -o lab3_4
./lab3_4
```

Windows PowerShell 執行 `./lab3_4.exe`。完整原始碼為 [`lab3_4.cpp`](../lab3_4.cpp)；機器可驗證範例在本目錄 `samples.json`。
