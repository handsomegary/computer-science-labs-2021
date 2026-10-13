# 2021 期中考 C：Tower of Hanoi：最少移動步驟

依提供的考卷與參考程式整理。題目採正式考卷，輸出字串以範例為準；必要的矛盾處理與補充行為於文末明列。

## 題目

有 A、B、C 三根柱子，n 個圓盤起初位於 A，從上到下依序編號 1–n，編號越大盤子越大。每次只能移動一個最上方的盤子，不能把大盤放到小盤上。請以最少步數把全部盤子搬到 C，依序列出每一步。必須使用回傳 void 的 Hanoi 函式。

## 輸入格式

一個整數 n，代表圓盤數。

## 輸出格式

每一步一行，精確格式 `move disk D from X to Y`，其中 D 是盤號，X、Y 為 A／B／C，最後換行。依範例不印輸入提示、不另印總步數；輸出本身共有 2^n−1 行。

## 限制與邊界

3 <= n <= 10。程式需先宣告 `void Hanoi(...);`，由 main 呼叫，main 後定義 Hanoi；允許自行選參數。最大輸出 1023 行。考卷不要求合法範圍外防呆；本實作對不合法 n 在 stderr 印 `Invalid disk count.` 與換行並回傳 1。

## 解法說明

把 n−1 個小盤由 source 移到 auxiliary，把盤 n 由 source 移到 target，再把 n−1 個小盤由 auxiliary 移到 target。空問題 n=0 不移動。T(n)=2T(n−1)+1，所以正好 2^n−1 步，達到最少步數；時間 O(2^n)，遞迴堆疊 O(n)。

## 考卷依據與採用規則

依提供的考卷與參考程式：柱子名稱、盤號、合法範圍與 void Hanoi 函式模板採考卷。文字提到一開始顯示提示，但 sample 沒有提示，因此以 sample 定輸出：只列移動，不加提示或總數。

## 範例

範例使用合法下界 n=3，七步完成。第一步必須從 A 到 C，與考卷範例一致。盤數 10 時仍採相同遞迴規則，只是輸出 1023 步。

以下是實跑的完整 stdout，不含終端機輸入回顯；範例獨立啟動程序，包含每個空格與換行。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
3
```

### 範例 1 輸出

```text
move disk 1 from A to C
move disk 2 from A to B
move disk 1 from C to B
move disk 3 from A to C
move disk 1 from B to A
move disk 2 from B to C
move disk 1 from A to C
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為本題解核心節錄，完整可編譯程式列於下一節。

```cpp
void Hanoi(int disks, char source, char auxiliary, char target)
{
    if (disks == 0) return;
    Hanoi(disks - 1, source, target, auxiliary);
    std::cout << "move disk " << disks << " from " << source << " to " << target << '\n';
    Hanoi(disks - 1, auxiliary, source, target);
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// Based on the provided exam and reference code.
#include <iostream>

void Hanoi(int disks, char source, char auxiliary, char target);

int main()
{
    int disks = 0;
    if (!(std::cin >> disks) || disks < 3 || disks > 10) {
        std::cerr << "Invalid disk count.\n";
        return 1;
    }
    Hanoi(disks, 'A', 'B', 'C');
    return 0;
}

void Hanoi(int disks, char source, char auxiliary, char target)
{
    if (disks == 0) return;
    Hanoi(disks - 1, source, target, auxiliary);
    std::cout << "move disk " << disks << " from " << source << " to " << target << '\n';
    Hanoi(disks - 1, auxiliary, source, target);
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `exams/2021/midterm` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic problem_c.cpp -o problem_c
./problem_c
```

Windows PowerShell 執行 `./problem_c.exe`。獨立原始碼：[problem_c.cpp](../problem_c.cpp)。範例亦保存在本目錄的 `samples.json`。
