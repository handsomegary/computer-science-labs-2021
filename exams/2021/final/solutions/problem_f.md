# 2021 期末 F：Average Score II：平均與不及格名單

> 完整重建版，非考卷逐字抄錄。已知規則與範例依2021期末考卷；歧義與缺漏以本頁明訂規則補齊。程式為獨立重新實作，公開內容只使用非個資範例。

## 題目

讀入1–50個整數成績，求平均並依輸入順序列出小於70分者。正式範例沒有先輸入N，因此N由實際成績數決定：讀至EOF，跨行或同一行都視為同一組分數。不要把第一個成績誤當作N。

## 輸入

stdin全部token都是分數，不另提供N。至少一個、至多50個，以空白或換行分隔，最後EOF。在互動終端機需送出EOF；以輸入檔執行會自動遇到EOF。

## 輸出

先印`Please enter the scores of all students:`與換行。再印`avg = V`。平均四捨五入到小數第二位，刪除無意義的尾零及小數點，因此40印40、47.50印47.5、0.13印0.13。若有分數<70，再印一次`fail:`，接著每筆`序號: 分數`各一行，序號從1開始。沒有不及格者不印fail。所有行換行。空輸入、超過50筆、非整數或分數超範圍時印error並回傳1。

## 限制與邊界

1≤N≤50，0≤score≤100；及格門檻為70。原文同時寫三位小數、N位小數與第二位捨入，相互矛盾；重建版採第二位四捨五入且刪尾零，以吻合正式40與47.5範例。

## 範例

stdout只包含程式輸出，不含終端機回顯的輸入。以下輸出已由C++11編譯後實際捕捉。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
30
40
50
```

### 範例 1 輸出

```text
Please enter the scores of all students:
avg = 40
fail:
1: 30
2: 40
3: 50
```

### 範例 2 輸入

```text
20
40
60
70
```

### 範例 2 輸出

```text
Please enter the scores of all students:
avg = 47.5
fail:
1: 20
2: 40
3: 60
```
<!-- SAMPLES_END -->

範例說明：第一例平均40，三筆都小於70。第二例平均(20+40+60+70)/4=47.5，只有前三筆不及格，70分不列出。

## 解法

用50格整數陣列保存，累加sum。百分位平均的整數結果為(sum×100+N/2)/N，正分數下等價四捨五入到第二位；以商、餘數輸出並刪尾零，避免浮點捨入誤差。最後掃描陣列列出所有低於70者。時間O(N)、空間O(N)。

## 考卷已知與重建補定

考卷已知：考卷明定1–50筆、0–100分、低於70不及格、輸入順序及fail格式；兩個正式範例確認沒有獨立N、整數與一位小數可以直接印。

重建補定：讀完整stdin至EOF、不在第一個換行提早停止、二位四捨五入／刪尾零、非法分數處理。這些補定解決原文與既有換行讀取方法的歧義。

## 完整題解程式

獨立來源：[../problem_f.cpp](../problem_f.cpp)。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2021 final F: infer N from all scores up to EOF; round to two decimal places.
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main() {
    cout << "Please enter the scores of all students:\n";
    int scores[50], count = 0, sum = 0;
    string token;
    while (cin >> token) {
        istringstream parser(token);
        int score;
        if (!(parser >> score) || parser.peek() != char_traits<char>::eof() ||
            score < 0 || score > 100 || count == 50) { cout << "error\n"; return 1; }
        scores[count++] = score;
        sum += score;
    }
    if (!cin.eof() || count == 0) { cout << "error\n"; return 1; }
    const int rounded = (sum * 100 + count / 2) / count;
    const int fraction = rounded % 100;
    cout << "avg = " << rounded / 100;
    if (fraction) {
        cout << '.';
        if (fraction % 10 == 0) cout << fraction / 10;
        else cout << setfill('0') << setw(2) << fraction;
    }
    cout << '\n';
    bool failed = false;
    for (int i = 0; i < count; ++i) if (scores[i] < 70) failed = true;
    if (failed) {
        cout << "fail:\n";
        for (int i = 0; i < count; ++i) if (scores[i] < 70) cout << i + 1 << ": " << scores[i] << '\n';
    }
}
```
<!-- SOLUTION_CODE_END -->
