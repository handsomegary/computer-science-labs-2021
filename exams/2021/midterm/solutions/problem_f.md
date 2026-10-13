# 2021 期中考 F：Postage Stamps：最大連續可付金額

依提供的考卷與參考程式整理。題目採正式考卷，輸出字串以範例為準；必要的矛盾處理與補充行為於文末明列。

## 題目

每份文件最多貼 h 張郵票，可以設計 k 種不同的正整數面額，每種郵票供應不限。對選定面額，求從1開始每個整數金額都能用最多h張郵票湊出的最大連續上界。選擇最佳面額，使此上界最大，輸出 n(h,k)。可以重複使用同一面額；不要求恰好用滿h張。

## 輸入格式

多組資料，每行兩個整數 h、k。0 0為終止記號，其餘正常資料h、k均為正整數。

## 輸出格式

每組輸出一行十進位最大連續可付金額n(h,k)，最後換行。0 0不印任何內容。依考卷最終輸出段落與sample，只印上界，不印最佳面額集合、提示或告別詞。

## 限制與邊界

h>=1、k>=1、h+k<=9，因此各參數最多8，共36組合法參數。面額為互異正整數，排列為嚴格遞增；第一個面額必須是1，否則不能支付1。程式必須搜尋最佳值，不能硬編碼答案表。重複輸入可快取已計算結果。範圍外參數在stderr印 `Invalid stamp limits.` 與換行並回傳1；EOF正常結束。

## 解法說明

對部分面額集合以minimumStamps[v]記錄支付v的最少張數，超過h的值統一用h+1表示。加入面額d時，先複製舊DP，再由小到大更新dp[v]=min(dp[v],dp[v−d]+1)，因此同一新面額可以用多張。掃描首次不能在h張內支付的值，得到當前連續上界N。

深度優先搜尋下一面額d，只枚舉previous<d<=N+1。若d>N+1，現有集合不能付N+1，往後更大面額也補不了此缺口，所以這類分支不可能更優。每加入一個面額，整體上界至多h(N+1)，反覆套用得到剩餘層的樂觀上界；不超過目前best時可剪枝。合法h+k<=9時DP的理論最大上界不超過1364，因此不需搜尋無限金額。

若S為實際搜尋節點數、V為最大DP大小，時間O(SV)、遞迴保留各層DP的空間O(kV)。快取只保存本次執行中已搜尋出的答案，起初全部為0，不是預存答案表。

## 考卷依據與採用規則

依提供的考卷與參考程式：最多h張、k種面額、單位正整數、最大從1連續可付金額、多組h+k<=9、0 0終止採考卷。敘述提到尋找最佳面額，但正式輸出段落與sample只印n，因此只輸出上界。非終止資料採正h、正k；此為有實際支付與面額的正常定義。

## 範例

h=3、k=2時面額1與3可以支付1–7，8無法在3張內湊成，因此上界7；所有候選面額搜尋後確認7為最大。h=5、k=1只能以面額1支付1–5，答案5。範例2檢查h+k=9兩個極端：h=1、k=8選1–8得8；h=8、k=1得8。

以下是實跑的完整 stdout，不含終端機輸入回顯；範例獨立啟動程序，包含每個空格與換行。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
3 2
5 1
0 0
```

### 範例 1 輸出

```text
7
5
```

### 範例 2 輸入

```text
1 8
8 1
0 0
```

### 範例 2 輸出

```text
8
8
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為本題解核心節錄，完整可編譯程式列於下一節。

```cpp
for (int denomination = consecutive + 1; denomination > previous; --denomination) {
    std::vector<int> next(maximumStamps * denomination + 1, maximumStamps + 1);
    std::copy(minimumStamps.begin(), minimumStamps.end(), next.begin());
    for (int value = denomination; value < static_cast<int>(next.size()); ++value)
        if (next[value - denomination] < maximumStamps)
            next[value] = std::min(next[value], next[value - denomination] + 1);
    searchDenominations(maximumStamps, denominationCount, selected + 1, denomination,
                        coverage(next, maximumStamps), next, best);
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// Based on the provided exam and reference code.
// Search denominations and compute exact coverage; no answer table is hardcoded.
#include <algorithm>
#include <iostream>
#include <vector>

int coverage(const std::vector<int>& minimumStamps, int maximumStamps)
{
    int value = 1;
    while (value < static_cast<int>(minimumStamps.size()) && minimumStamps[value] <= maximumStamps) ++value;
    return value - 1;
}

void searchDenominations(int maximumStamps, int denominationCount, int selected,
                         int previous, int consecutive, const std::vector<int>& minimumStamps,
                         int& best)
{
    if (selected == denominationCount) {
        best = std::max(best, consecutive);
        return;
    }
    // Even the next denomination cannot exceed the first uncovered value.
    // Adding another denomination can cover no more than h*(coverage+1).
    int optimistic = consecutive;
    for (int remaining = selected; remaining < denominationCount; ++remaining)
        optimistic = maximumStamps * (optimistic + 1);
    if (optimistic <= best) return;

    for (int denomination = consecutive + 1; denomination > previous; --denomination) {
        std::vector<int> next(static_cast<std::size_t>(maximumStamps * denomination + 1), maximumStamps + 1);
        std::copy(minimumStamps.begin(), minimumStamps.end(), next.begin());
        for (int value = denomination; value < static_cast<int>(next.size()); ++value) {
            if (next[value - denomination] < maximumStamps)
                next[value] = std::min(next[value], next[value - denomination] + 1);
        }
        searchDenominations(maximumStamps, denominationCount, selected + 1, denomination,
                            coverage(next, maximumStamps), next, best);
    }
}

int optimumCoverage(int maximumStamps, int denominationCount)
{
    // Denomination 1 is necessary to make the first value of the sequence.
    std::vector<int> minimumStamps(static_cast<std::size_t>(maximumStamps + 1));
    for (int value = 0; value <= maximumStamps; ++value) minimumStamps[value] = value;
    int best = 0;
    searchDenominations(maximumStamps, denominationCount, 1, 1, maximumStamps, minimumStamps, best);
    return best;
}

int main()
{
    int cached[9][9] = {};
    int maximumStamps = 0, denominationCount = 0;
    while (std::cin >> maximumStamps >> denominationCount) {
        if (maximumStamps == 0 && denominationCount == 0) return 0;
        if (maximumStamps < 1 || denominationCount < 1 || maximumStamps > 8
            || denominationCount > 8 || maximumStamps + denominationCount > 9) {
            std::cerr << "Invalid stamp limits.\n";
            return 1;
        }
        int& answer = cached[maximumStamps][denominationCount];
        if (answer == 0) answer = optimumCoverage(maximumStamps, denominationCount);
        std::cout << answer << '\n';
    }
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `exams/2021/midterm` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic problem_f.cpp -o problem_f
./problem_f
```

Windows PowerShell 執行 `./problem_f.exe`。獨立原始碼：[problem_f.cpp](../problem_f.cpp)。範例亦保存在本目錄的 `samples.json`。
