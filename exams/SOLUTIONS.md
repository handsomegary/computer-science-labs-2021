# 考古題與完整 solution

110 學年度第一學期（2021 課程）期中 6 題、期末 7 題，合計 13 題。每頁都有繁中題目、輸入輸出、採用規則、實測範例、解法及完整 C++11 程式碼。

| 考試 | 題號 | 題目與完整 solution | 獨立程式 |
| --- | --- | --- | --- |
| 期中 | A | [2021 期中考 A：雞兔同籠](2021/midterm/solutions/problem_a.md) | [problem_a.cpp](2021/midterm/problem_a.cpp) |
| 期中 | B | [2021 期中考 B：逐次數位加總](2021/midterm/solutions/problem_b.md) | [problem_b.cpp](2021/midterm/problem_b.cpp) |
| 期中 | C | [2021 期中考 C：Tower of Hanoi：最少移動步驟](2021/midterm/solutions/problem_c.md) | [problem_c.cpp](2021/midterm/problem_c.cpp) |
| 期中 | D | [2021 期中考 D：區間內的 Armstrong Numbers](2021/midterm/solutions/problem_d.md) | [problem_d.cpp](2021/midterm/problem_d.cpp) |
| 期中 | E | [2021 期中考 E：極值平均與十進位／八進位／二進位](2021/midterm/solutions/problem_e.md) | [problem_e.cpp](2021/midterm/problem_e.cpp) |
| 期中 | F | [2021 期中考 F：Postage Stamps：最大連續可付金額](2021/midterm/solutions/problem_f.md) | [problem_f.cpp](2021/midterm/problem_f.cpp) |
| 期末 | A | [2021 期末 A：Spiral Graph II：外擴螺旋](2021/final/solutions/problem_a.md) | [problem_a.cpp](2021/final/problem_a.cpp) |
| 期末 | B | [2021 期末 B：Build a Tree：七節點搜尋樹](2021/final/solutions/problem_b.md) | [problem_b.cpp](2021/final/problem_b.cpp) |
| 期末 | C | [2021 期末 C：Buy and Sell Stock：不限交易次數的最大利潤](2021/final/solutions/problem_c.md) | [problem_c.cpp](2021/final/problem_c.cpp) |
| 期末 | D | [2021 期末 D：Is Anagram：字母重排判斷](2021/final/solutions/problem_d.md) | [problem_d.cpp](2021/final/problem_d.cpp) |
| 期末 | E | [2021 期末 E：Encryption System：交錯位移](2021/final/solutions/problem_e.md) | [problem_e.cpp](2021/final/problem_e.cpp) |
| 期末 | F | [2021 期末 F：Average Score II：平均與不及格名單](2021/final/solutions/problem_f.md) | [problem_f.cpp](2021/final/problem_f.cpp) |
| 期末 | G | [2021 期末 G：NCU Theater Reservation System VII](2021/final/solutions/problem_g.md) | [problem_g.cpp](2021/final/problem_g.cpp) |

[JSON 題目集](problems.json) 的每筆 `solution.code` 都包含完整程式碼；檔案型題目的範例附件在 `examples[].files`。

執行 `python tools/sync_exam_solutions.py` 可同步文件；CI 檢查同步狀態、編譯 solution 內嵌程式碼，並逐筆實測範例。
