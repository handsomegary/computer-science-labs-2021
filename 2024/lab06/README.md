# 2024 Lab 6：函式

依據課程的 `2024Fall_EE1007_CSLab_Lab6_20241026.pdf`，逐頁檢查文字與程式碼圖片後獨立實作。2024 題目與提供的原始程式資料夾的 2021 題目不同，這些檔案沒有沿用 2021 題號的答案。未把講義原檔放入 repo。

講義是教學／Review 提示，部分題目沒有完整 `main`、原始 OJ 題面、輸入範圍或輸出範例。下表明列本 repo 的可執行介面；測試驗證這個介面，不代表已取得原 OJ 的 Accepted。

從 repo 根目錄編譯單一題目：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic 2024/lab06/lab6_1.cpp -o lab6_1
./lab6_1
```

Windows 執行 `lab6_1.exe`，替換檔名可執行其他題。

| 題目與程式 | 輸入與輸出 | 必要函式與修正 |
| --- | --- | --- |
| P113021 Minimum Number，`lab6_1.cpp` | 三個有限浮點數；輸出最小值，最多 15 位有效數字 | 使用指定的 `double minimum(double, double, double)` 回傳結果，沒有全域變數傳結果。講義未指定提示或小數格式，採一行純數值。 |
| P113022 LCM，`lab6_2.cpp` | 兩個正 `int`；輸出最小公倍數 | 保留 `int LCM_calculator(int, int)`。以 Euclid GCD 後先除再乘取代逐一試數，時間 O(log n)；0、負數及超出 `int` 的答案輸出 `error`，避免除零、無窮迴圈與溢位。講義未列數值範圍，函式指定的 `int` 是答案儲存限制。 |
| P113023 Electrical Appliance Store，`lab6_3.cpp` | 重複輸入進店 Y/N、會員 Y/N、消費額；N 離開 | 使用指定的 `enterStore()`、`hasMembershipCard()`、`calculateRewards(bool, int)`，提示與獎勵文字依講義圖片。消費額提示在講義缺少完整 `main`，採 `Enter the money you spent:`。非法選擇重試，EOF 正常結束。 |
| P113024 People's Commune，`lab6_4.cpp` | 兩個不同正容量 X、Y，再輸入正目標 Z；輸出 1／0 表示可否量出 | 使用 `gcd`、`canMeasureWater`；判斷 Z ≤ X+Y 且 Z 是 GCD 倍數。容量接受正 `int` 範圍，總容量先用 64 位元計算。講義未提供最終訊息，採布林數值格式。 |

商店獎勵依程式碼圖片的邊界如下：

| 會員狀態 | 消費區間 | 獎勵 |
| --- | --- | --- |
| 有 | < 5000 | 500 元優惠券 |
| 有 | 5000–10000 | 1000 元優惠券 |
| 有 | > 10000 | 3000 元優惠券及一張彩券 |
| 無 | < 7000 | 無獎勵 |
| 無 | 7000–10000 | 500 元優惠券 |
| 無 | > 10000 | 1500 元優惠券並成為會員 |

執行 `python tests/test_2024_labs_6_9.py`；以 `--cxx` 或 `CXX` 指定編譯器。測試涵蓋最小值正負與相等、LCM 大數與溢位、所有優惠邊界，以及兩鍋容量相加超出 `int` 的情況。
