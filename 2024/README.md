# 2024 年課程

本目錄依提供的 2024 Lab 3–12 講義、Review 及題解程式碼建立，每次四題，共 40 支可獨立編譯的 C++11 程式。依使用者要求，題面不完整的部分已補定成完整練習題，並明確標為**重建版，非教授原題**。2021 的 47 題保留在 repo 根目錄 `lab01`–`lab14`。

**[40 題完整題目與 solution 索引](SOLUTIONS.md)**：每頁有題目、輸入輸出、限制、實測範例、題解核心片段、解法說明及完整 C++11 程式碼。程式碼直接嵌在 solution 裡，不只提供外部連結。另有 [機器可讀題目集](problems.json)，完整程式碼保存於每筆的 `solution.code`。

| 目錄 | 四個題目 |
| --- | --- |
| `lab03` | Candy Bar、Height Limitation、Palindrome、Find the Bomb |
| `lab04` | Annual Interest Calculator、Company Investment Comparison、Luggage Allocation、Banking System |
| `lab05` | Calculator、Combination、Debugging、Monopoly Game |
| `lab06` | Minimum Number、LCM、Electrical Appliance Store、The People's Commune |
| `lab07` | Triangle、Oil Lamp、Almost Prime Numbers、Feistel Cipher |
| `lab08` | Combination Calculator、Rectangle Partitioning、Candy Distribution、Calculate the Score |
| `lab09` | Parity、Maximum Path Sum（區間加總）、Lexicographical Ordering、Local Binary Patterns |
| `lab10` | Modifying Score、Transpose Matrix、Book Arrangement、Decrypting Message |
| `lab11` | Price Discount、Date、Booking System、Apple and Banana |
| `lab12` | Reverse Output of an Array、Digital Root、Booking System II、Maze |

## 重建方式

提供的 PDF 多為解題提示、流程圖與程式截圖。本次由詳解與現有完整解法反推題意；講義可確認的演算法、資料結構、函式與字串保留，未給出的提示、讀取順序、格式、邊界或勝負規則則補成明確定義。每題分開列出講義規則與補定規則。測試驗證本 repo 的完整重建題目，未宣稱是原課程隱藏測資的 Accepted 結果。

原先影響答案的缺漏，現在採以下完整重建規則：

- Lab 7.3：正式重建題意採 semiprime（含重複因子的兩個質因數），輸出十進位、二進位與十六進位；其他兩種定義保留為延伸模式。
- Lab 7.4：四個控制索引、輪數及每輪 KEY／F 都是明確輸入，照題解完成各個運算部件與正反向流程；不需要未提供的 generator 公式。[完整題目與 solution](lab07/solutions/lab7_4.md)。
- Lab 5.4：結束時比較兩人的分數決定勝負；題目已列出移動、轉角、字元分數與當輪結束順序。

未提供的 Lab 1、2 或 Lab 12 後續講義不在本目錄補造。Lab 5 Debugger 是操作教學補充，沒有另編一題。

## 編譯與測試

在 repo 根目錄，例如：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic 2024/lab12/lab12_4.cpp -o y2024_lab12_4
python tools/verify.py --cxx g++
```

每支程式各有自己的 `main`，不要同時連結多題；CMake target 都有 `y2024_` 前綴。各題 I/O 範例和需要的執行流程見所屬目錄 README。

測試使用 Python 標準函式庫、暫存目錄及獨立答案模型，包含箱子分配窮舉、公曆計算、組合數、排列、質因數定義、Feistel 位元排列、LBP、Caesar、訂房庫存、猜數字及迷宮可達性。另直接編譯 solution 內嵌的 40 支程式，核對每頁的實測範例。測試產物不保存於 repo。課程講義 PDF 未納入版本控制。
