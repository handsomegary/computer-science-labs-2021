# 計算機概論實習考古題

本目錄完成 110 學年度第一學期（2021 課程）的期中與期末程式題，共 13 題。以提供的正式考卷、範例與參考程式核對題意，修正邊界、溢位、資料結構與互動流程問題。每題都有可獨立編譯的 C++11 程式，完整程式碼也直接包含在 solution 裡。

從 **[13 題完整題目與 solution 索引](SOLUTIONS.md)** 開始。另有 [JSON 題目集](problems.json)，每筆的 `solution.code` 保存全文，`examples[].files` 保存檔案型題目的範例附件。

| 考試 | 位置 | 題目 |
| --- | --- | --- |
| 期中 A–F | `2021/midterm` | 雞兔同籠、逐次數位加總、河內塔、Armstrong number、收入進位轉換、最優郵票面額 |
| 期末 A–G | `2021/final` | 螺旋圖、BST 後序遍歷、股票最大收益、Anagram、加解密 class、平均與不及格清單、劇院會員電話 |

## 題目與範例

題面整理為繁體中文，保留考卷的演算法、結構／class 要求與英文輸出。考卷文字、排版或範例互相矛盾的地方，各題文件會明列採用規則；不把補定的介面宣稱為確定的原判題格式。測試驗證此處列出的完整規格，尚未送交原課程 OJ。

股票檔案保留題目資料格式。會員與加解密範例採中性合成資料，會員檔包含的名稱、密碼和電話僅供練習。原考卷、原作者程式副本、執行截圖與作者評比均不納入此 repo。

期中預習資料中的 Lab 範例已由 repo 根目錄的 `lab01`–`lab14` 覆蓋；本目錄依正式期中 A–F、期末 A–G 整理，不將預習 Lab 重複算成考題。

## 編譯與執行

在 repo 根目錄逐題編譯，例如：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic exams/2021/midterm/problem_f.cpp -o midterm_f
g++ -std=c++11 -Wall -Wextra -Wpedantic exams/2021/final/problem_g.cpp -o final_g
```

每支 `.cpp` 都有自己的 `main`。CMake target 以 `exam2021_midterm_` 或 `exam2021_final_` 開頭，避免與其他年份和考試同名題目衝突。

檔案型題目從執行工作目錄讀取檔名；例如在 repo 根目錄執行期末 G，命令 7 的檔名可輸入 `exams/2021/final/fixtures/member1.txt`。文件中的範例附件則先建立在範例執行目錄中，再提供範例的短檔名。

## 驗證

```sh
python tools/verify.py --cxx g++
python tools/sync_exam_solutions.py --check
```

測試包含官方範例、合法邊界、獨立答案模型、檔案讀取、會員與座位狀態，以及直接編譯文件內嵌的完整 solution。執行檔與範例工作檔建立於暫存目錄，測試結束後清除。
