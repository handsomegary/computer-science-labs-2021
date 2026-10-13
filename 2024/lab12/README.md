# 2024 Lab 12：Pointer II

<!-- SOLUTIONS_NAV_BEGIN -->
## 完整重建題目與 solution

以下各頁包含明確題目、補定規則、實測範例、題解核心片段與完整 C++11 程式碼。

- [Lab 12.1 題目與 solution](solutions/lab12_1.md)
- [Lab 12.2 題目與 solution](solutions/lab12_2.md)
- [Lab 12.3 題目與 solution](solutions/lab12_3.md)
- [Lab 12.4 題目與 solution](solutions/lab12_4.md)

[全部 40 題索引](../SOLUTIONS.md) · [problem / solution 資料集](../problems.json)
<!-- SOLUTIONS_NAV_END -->

依 **2024Fall_EE1007_CSLab_Lab12_20241216.pdf** 獨立實作；四個 `.cpp` 皆可單獨編譯及提交。

```sh
g++ -std=c++11 -O2 -Wall -Wextra -Wpedantic lab12_1.cpp -o lab12_1
```

其他題改成 `lab12_2`、`lab12_3`、`lab12_4`。Linux/macOS 執行 `./lab12_1`，Windows 執行對應 `.exe`。

| 程式 / 題號 | 輸入 | 輸出與必要概念 |
| --- | --- | --- |
| `lab12_1.cpp` / P113041 Reverse Output of an Array | 五個 `int` 整數 | 存入五元素陣列，傳入函式並倒序輸出，以單一空白分隔。所有陣列存取都使用指標算術。 |
| `lab12_2.cpp` / P113042 Digital Root | 一個 `int` 整數 | 呼叫 `void digitalRoot(int num, int *dRoot)`，經指標累加各位數，再重複至個位數；只在 `main` 輸出 `digital root: X`。 |
| `lab12_3.cpp` / P113043 Booking System II | 與 2024 Lab 11.3 相同的訂房互動 | 使用講義指定的 `vector<vector<string>> not_available` 紀錄日期與房號。每種房型每一天只有一間；拒絕重複預訂，搜尋只列尚未訂出的房型，沒有符合房間的飯店不顯示。 |
| `lab12_4.cpp` / P113044 Maze | 先輸入 `rows columns`，接著 `rows×columns` 個 0/1；可用緊接的字串或空白分隔 | 0 可走、1 是牆；由左上至右下，以講義的上下文採上、右、下、左順序 DFS，使用指標及顯式 stack。找到時輸出 `(row, column)` 座標串，否則 `Can't reach the exit!`。 |

12.2 第 5 頁明訂 `int *dRoot`，但第 7 頁程式圖片誤用 `int &dRoot`；本實作遵守**明訂的指標型別**。提供的檔案沒有完整原始 `.cpp` 範本，所以依第 7 頁 main 的 `do/while` 還原，將解題內容放在 `// CODE BEGIN` 與 `// CODE END` 間。若使用另有的官方完整範本，將該區塊放入其指定位置即可。0 的 digital root 為 0；另外安全支援負數與 `INT_MIN` 的絕對數值，避免 `abs(INT_MIN)` 溢位。

12.3 保留 [Lab 11 的飯店房型、價格、輸入格式](../lab11/README.md)。投影片有明示的錯誤訊息保留為 `Wrong number, please enter again!`、`The selected room is not available, please enter again!`，成功為 `Reserved successfully!`。庫存以正規化日期和房號配對，因此換一天就有獨立庫存，同一天 `9/6` 與 `09/06` 算相同。這些日期正規化與完整首頁文字是為缺漏的 OJ 對話建立的本實作契約。

12.4 的座標從 0 起算。利用外圈牆壁避免邊界越界；走訪標記避免循環；動態配置 stack，避免投影片固定大小可能造成溢位。入口或出口是牆時顯示無解，1×1 開放迷宮直接輸出 `(0, 0)`。DFS 給出一條可行路徑，不保證最短。

迷宮範例：

```text
輸入：
2 3
000
000
輸出：
(0, 0) (0, 1) (0, 2) (1, 2)
```

投影片沒有 Maze 的完整 main 輸入提示，故採用上述維度加字元矩陣格式，不額外印輸入提示。Reverse Array 也只輸出結果。三題算法與投影片指定的指標存取方式一致。

repo 根目錄執行 `python tests/test_2024_labs_10_12.py`。測試以獨立 BFS 檢查迷宮可達性，再檢查輸出路徑每一步合法且不重複；另測 100×100 長蛇迷宮、單一格、死路、無路、digital root 邊界、房間庫存、日期隔離與空飯店隱藏。
