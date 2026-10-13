# 2021 期末 D：Is Anagram：字母重排判斷

> 完整重建版，非考卷逐字抄錄。已知規則與範例依2021期末考卷；歧義與缺漏以本頁明訂規則補齊。程式為獨立重新實作，公開內容只使用非個資範例。

## 題目

給定兩個只含a–z的小寫字串，判斷能否將第一個字串的所有字母重新排列而得到第二個。每個字母必須使用恰好相同次數；只是使用相同種類的字母並不足夠。

## 輸入

兩個非空小寫字串，以空白或換行分隔。

## 輸出

是anagram時印`Yes! It's anagram.`，否則印`No! It is not anagram.`，最後換行。字元或長度不合法、讀取失敗時印error並回傳1。

## 限制與邊界

各字串長度1–1000000，只能含ASCII a–z。考卷未訂長度上限，1000000為重建版的實用界線。

## 範例

stdout只包含程式輸出，不含終端機回顯的輸入。以下輸出已由C++11編譯後實際捕捉。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
anagram naagrma
```

### 範例 1 輸出

```text
Yes! It's anagram.
```

### 範例 2 輸入

```text
rat cat
```

### 範例 2 輸出

```text
No! It is not anagram.
```
<!-- SAMPLES_END -->

範例說明：第一例兩字串的a出現三次，其餘n、g、r、m各一次，因此相同。第二例rat含r，而cat含c，故不同。

## 解法

建立26個整數的頻率差，第一個字串遇字母加一，第二個減一。最後所有差為0，才能重新排列成彼此。時間O(|s1|+|s2|)，額外空間O(26)。長度不同自然會留下非零頻率差。

## 考卷已知與重建補定

考卷已知：考卷定義字母重排、僅含a–z，並給出兩個精確結果字串及範例。

重建補定：非空、實用長度上限及非法輸入的error處理；合法資料的輸出完整遵循正式範例。

## 完整題解程式

獨立來源：[../problem_d.cpp](../problem_d.cpp)。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2021 final D: compare lowercase-letter multiplicities.
#include <iostream>
#include <string>
using namespace std;
int main() {
    string first, second;
    if (!(cin >> first >> second) || first.size() > 1000000 || second.size() > 1000000) {
        cout << "error\n";
        return 1;
    }
    int counts[26] = {};
    for (size_t i = 0; i < first.size(); ++i) {
        if (first[i] < 'a' || first[i] > 'z') { cout << "error\n"; return 1; }
        ++counts[first[i] - 'a'];
    }
    for (size_t i = 0; i < second.size(); ++i) {
        if (second[i] < 'a' || second[i] > 'z') { cout << "error\n"; return 1; }
        --counts[second[i] - 'a'];
    }
    bool anagram = true;
    for (int i = 0; i < 26; ++i) if (counts[i] != 0) anagram = false;
    cout << (anagram ? "Yes! It's anagram.\n" : "No! It is not anagram.\n");
}
```
<!-- SOLUTION_CODE_END -->
