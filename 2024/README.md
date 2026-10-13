# 2024 年課程

本目錄依提供的 2024 Lab 3–12 講義與 Review 實作，每次四題，共 40 支可獨立編譯的 C++11 程式。各年份題目以該年份資料為準；2021 的 47 題保留在 repo 根目錄 `lab01`–`lab14`。

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

## 資料完整度

提供的 PDF 多為解題提示、流程圖與程式截圖，沒有完整的原始 HydroOJ 題目。本目錄依可確認的演算法、資料結構、函式及顯示字串完成可執行版本；沒有給出的提示、讀取順序、格式或邊界，均在各 lab 的 README 註明選擇。測試驗證這些**公開記錄的介面**，並不等於原課程隱藏測資已通過。

影響計算答案的明顯缺漏：

- Lab 7.3 未定義 almost prime：標準編譯模式採 semiprime，另有 prime-power 與兩種不同質因數的模式；各自有獨立參考測試。
- Lab 7.4 未給 key 控制的完整排列、產生輪數的公式、每輪 KEY／F 選擇：程式實作截圖的完整運算部件，將這些規則作為明確設定輸入。詳見 `lab07/FEISTEL_SPEC.md`。
- Lab 5.4 Review 未提供完整勝負規則：本地版本以結束時分數比較，README 明示該決定。

未提供的 Lab 1、2 或 Lab 12 後續講義不在本目錄補造。Lab 5 Debugger 是操作教學補充，沒有另編一題。

## 編譯與測試

在 repo 根目錄，例如：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic 2024/lab12/lab12_4.cpp -o y2024_lab12_4
python tools/verify.py --cxx g++
```

每支程式各有自己的 `main`，不要同時連結多題；CMake target 都有 `y2024_` 前綴。各題 I/O 範例和需要的執行流程見所屬目錄 README。

測試使用 Python 標準函式庫、暫存目錄及獨立答案模型，包含箱子分配窮舉、公曆計算、組合數、排列、質因數定義、Feistel 位元排列、LBP、Caesar、訂房庫存、猜數字及迷宮可達性。測試產物不保存於 repo。課程講義 PDF 未納入版本控制。
