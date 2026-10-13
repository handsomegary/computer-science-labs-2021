# 2021 期中考 A–F

依提供的考卷與參考程式完成六題。所有 `.cpp` 可獨立以 C++11 編譯；每份題解都包含正式題目整理、精確輸入輸出、解法、核心片段、完整原始碼與實跑範例。

| 題目 | 程式 | 完整題解 |
| --- | --- | --- |
| A 雞兔同籠 | [problem_a.cpp](problem_a.cpp) | [題目與解法](solutions/problem_a.md) |
| B 逐次數位加總 | [problem_b.cpp](problem_b.cpp) | [題目與解法](solutions/problem_b.md) |
| C Hanoi | [problem_c.cpp](problem_c.cpp) | [題目與解法](solutions/problem_c.md) |
| D Armstrong Numbers | [problem_d.cpp](problem_d.cpp) | [題目與解法](solutions/problem_d.md) |
| E 極值平均與進位 | [problem_e.cpp](problem_e.cpp) | [題目與解法](solutions/problem_e.md) |
| F 郵票面額最佳化 | [problem_f.cpp](problem_f.cpp) | [題目與解法](solutions/problem_f.md) |

例如在此目錄執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic problem_a.cpp -o problem_a
./problem_a
```

Windows PowerShell 執行 `./problem_a.exe`。其他題替換檔名即可。範例的輸出是程式 stdout，不含使用者輸入回顯。

採用規則：C 依考卷範例只印移動步驟，不加提示或總步數；D 非空結果保留範例最後一個空格。B、D 依明列數值範圍接受 0。E 的 n 原文稱正整數但範圍含 0，空資料沒有極值，因此 n=0 視為需要重輸；平均非整數時重讀新的 n 與完整資料。F 依最後輸出規則與範例只印最大連續上界，不印面額清單。各題完整說明列在題解中。

D 以數位多重集合產生候選數，沒有線性掃描整個整數區間或預存答案表。F 搜尋遞增面額並以最少郵票數 DP 計算精確連續上界，答案由計算產生；只快取本次執行中的重複查詢。

由 repository 根目錄執行自含測試：

```sh
python tests/test_exam_2021_midterm.py
```

可用 `--cxx` 或 `CXX` 指定 C++ 編譯器。測試會在暫存目錄編譯六題，包含雞兔小範圍窮舉、數位加總字串模型、Hanoi 全部合法盤數的柱子狀態驗證、Armstrong 數位集合與小範圍掃描交叉比對、收入極值模型，以及郵票全部 36 組合法參數與小型面額集合的獨立最優搜尋。機器可驗證範例在 [samples.json](solutions/samples.json)。
