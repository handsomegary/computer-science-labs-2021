# 2024 Lab 3：Control Statement I

依據 `2024Fall_EE1007_CSLab_Lab3_Review_20241010` 的題目文字、流程圖與程式片段完成。四題都是 2024 題目，與 2021 Lab 3 不同。每支 `.cpp` 是獨立 C++11 程式。

| 程式 | 題目 | 講義明確規則與作法 |
| --- | --- | --- |
| `lab3_1.cpp` | P113009 Candy Bar | 先讀總糖果數；有糖果時輸出開店訊息，使用 `while` 反覆讀取拿取數量；清空時輸出關店訊息。 |
| `lab3_2.cpp` | P113010 Height Limitation | 讀三人身高與遊樂設施編號；使用 `if/else`。設施 1／2／3 最低身高分別 140／120／100，等於門檻可搭乘。 |
| `lab3_3.cpp` | P113011 Palindrome | 使用 `while` 與 `if/else` 判斷數字回文，輸出講義片段中的 `YES` 或 `NO`。 |
| `lab3_4.cpp` | P113012 Find the Bomb | 炸彈與猜測都必須嚴格位於上下界之間；依猜測縮小範圍，錯誤輸入重新讀取。 |

在本目錄，例如：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab3_1.cpp -o lab3_1
./lab3_1
```

其他題替換檔名；Windows 執行 `./lab3_1.exe`。輸入都是以空白或換行分隔的數值：

- Candy Bar：`10 3 7`，開店兩次後關店。保留 `The candy bar is open!`、`How many candy do you want to take: `、`The candy bar is closed!`。
- Height Limitation：`139 140 150 1`，輸出 `2`。
- Palindrome：`16461`，輸出 `YES`；`12345` 輸出 `NO`。
- Find the Bomb：`50 65 30 50`，範圍依序 0–100、0–65、30–65，結果為炸彈 50、有效猜測 3 輪。

**來源缺漏與本地介面決定：** Review 未提供 Lab 3.1 的初始總數提示、Lab 3.2 的提示／最終句子、Lab 3.3 的輸入提示及 Lab 3.4 的最終句子。前面三題直接讀取數值，Lab 3.2 只印可搭乘人數；猜炸彈最後採 `Bomb number: N` 與 `Rounds: N` 兩行。這些是可執行介面，不宣稱是未提供的原始 OJ 字串。炸彈錯誤重試不計輪數。Review 未列其他數值範圍；程式支援非負糖果數、非負身高，回文以有號 64 位整數為輸入，負數定義為非回文。

修正與驗證：回文只反轉一半位數，避免 64 位整數反轉溢位；糖果拿超過剩餘數量時清空而不溢位；防呆與 EOF 都能正常終止。測試涵蓋身高門檻、最大整數、回文／非回文、猜測邊界、重試與輪數。完整 Review 不在 repository 中散布。
