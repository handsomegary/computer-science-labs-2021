# 2024 Lab 7：函式

依據課程的 `2024Fall_EE1007_CSLab_Lab7_20241105.pdf`，檢查流程圖與程式碼圖片後獨立實作。這組題目是三角形、油燈、Almost Prime 與 Feistel，不是 2021 的遞迴課題。

講義缺少原 OJ 完整題面與多數精確 I/O 範例。下列程式可編譯執行；指定函式與明確規則按講義完成，缺少的介面採公開的參考 contract，不能視為原 OJ 已 Accepted。

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic 2024/lab07/lab7_1.cpp -o lab7_1
./lab7_1
```

Windows 執行 `lab7_1.exe`；替換檔名可編譯其餘題。

| 程式 | 可執行介面與規則 | 課程要求與修正 |
| --- | --- | --- |
| P113025 Triangle，`lab7_1.cpp` | 輸入三個正 `int` 邊長；印 `perimeter:`、`area:`。不成三角形印 `error` | 使用兩個 `void` 函式。避免圖片範例的整數除二截斷半周長，以及先用 `int` 相加造成的溢位。面積採預設六位有效數字，講義未另定小數位數。 |
| P113026 Oil Lamp，`lab7_2.cpp` | 輸入 0–2⁶³−1，完全平方數印 `on`，其他印 `off` | 以函式及整數二分搜尋判斷，除法比較避免平方溢位與浮點近似；0 按數學上的完全平方數處理。原題未列輸入範圍或 on/off 的精確字樣，這是本 repo 明訂介面。 |
| P113027 Almost Prime，`lab7_3.cpp` | **Review 參考實作**：兩個非負整數為含端點區間；輸出數量的 `decimal:`、`binary:`、`hex:` 三行 | 至少一個運算函式，沒有陣列、vector、`std::string`。預設使用含重複因子的恰好兩個質因數，即 semiprime；可切換下列定義。 |
| P113028 Feistel，`lab7_4.cpp` | **Review 參考實作**：四個 key、四個控制索引、四個資料 byte／字元、輪數，再逐輪明訂 E/D、KEY 與 F | 完成講義可確認的 scramble、16-bit 整合、XOR／AND／OR／逐 byte MOD 與 Feistel 正向／反向輪；沒有陣列、vector、string。原題沒有提供的 key 控制、輪數與排程作為明確設定輸入；詳細介面、範例與缺口見 [FEISTEL_SPEC.md](FEISTEL_SPEC.md)。 |

Almost Prime 的講義只提到計算區間內數量、檢查因數、轉二進位或十六進位，**沒有定義 Almost Prime，也沒有說明如何選擇進位或列出輸出格式**。因此提供三種明確定義，使用編譯選項切換：

```sh
# 預設 0：semiprime，p*q；p 與 q 可以相同，例如 4、6、9，排除 8。
g++ -std=c++11 2024/lab07/lab7_3.cpp -o almost_prime
# 1：prime power，p^k 且 k>=2，例如 4、8、9，排除 6。
g++ -std=c++11 -DALMOST_PRIME_MODE=1 2024/lab07/lab7_3.cpp -o prime_power
# 2：恰好兩個不同質因數，例如 6、12、18，排除 4、8。
g++ -std=c++11 -DALMOST_PRIME_MODE=2 2024/lab07/lab7_3.cpp -o two_distinct
```

三種模式都計算區間數量，保留數字重複因子的差別；二進位與十六進位以逐位遞迴輸出，0 也印出一位。因數試除的時間約為區間長度乘上上限平方根，適合課堂規模資料；接近 64 位元上限的寬區間會耗時。原 OJ 的定義、進位選擇與輸出格式仍需原題面核對。

執行 `python tests/test_2024_labs_6_9.py`，涵蓋三角形半周長、接近 2⁶³−1 的完全平方數及三種 Almost Prime 定義。Feistel 的測試另列於 `tests/test_2024_lab7_4.py`。
