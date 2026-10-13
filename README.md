# 計算機概論實習：2021 與 2024

依國立中央大學 EE1007「Introduction to Computer Science Laboratory」各年份自己的課程講義整理。2021 以提供的原始程式碼補完與修正；2024 依該年份不同的題目實作。講義與原程式資料夾為核對來源；本 repo 保存獨立 C++11 程式、使用說明與自動測試。

## 使用

| 年份 | 位置 | 題目範圍 |
| --- | --- | --- |
| 2021 | 根目錄 `lab01` 到 `lab14` | Lab 1–14，共 47 題，另有 Lab 6.1 大數延伸版 |
| 2024 | `2024/lab03` 到 `2024/lab12` | Lab 3–12，共 40 個可執行實作；Review 缺少的原題規則與介面另列說明 |

年份相同的題號也可能對應不同題目，請先選年份，再看各目錄的 README。每個 `labX_Y.cpp` 都有自己的 `main`，請逐題編譯，不要將多個作業一起連結。需依學校繳交規定命名時，可把該題檔案改為指定的「學號_姓名_LabX.Y.cpp」。2021 Lab 1.2 的姓名、學校與學號使用占位文字，可依繳交需求自行填寫。

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab14/lab14_1.cpp -o lab14_1
./lab14_1
```

2024 範例：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic 2024/lab06/lab6_1.cpp -o y2024_lab6_1
./y2024_lab6_1
```

也可選擇以 CMake 一次編譯所有題目：

```sh
cmake -S . -B build
cmake --build build
```

2021 的 CMake target 保留 `labX_Y`；2024 的 target 為 `y2024_labX_Y`，避免不同年份同名題號衝突。

Windows 的 Code::Blocks 可為每題建立 Console application，將該題程式設為唯一來源，啟用 `-std=c++11`。需要輸入檔的題目，請依各 lab 的 README 準備檔案及設定執行工作目錄。

## 自動驗證

測試僅依賴 Python 標準函式庫與 C++ 編譯器，執行檔放在暫存目錄，結束後刪除。

```sh
python tools/verify.py --cxx g++
```

Windows 範例：

```powershell
python tools/verify.py --cxx 'C:\Program Files\CodeBlocks\MinGW\bin\g++.exe'
```

GitHub Actions 在每次 push 與 pull request 執行相同檢查。測試涵蓋範例、錯誤輸入、數值邊界與互動流程；題目指定的遞迴、陣列、指標、結構、class 等寫法另依講義核對。這些檢查不代表已送交原課程的 HydroOJ 判題。

## 範圍與來源

- 使用 2021 Lab 1–14；Lab 14 的授課日期為 2022/01/06。
- Lab 5 只有 review 講義，因此依該 review 與現有程式碼還原三題，細節列於 `lab05/README.md`。
- Lab 13 以更新版講義為準。
- 2024 提供的資料包含 Lab 3–5 Review、Lab 5 Debugger 補充，以及 Lab 6–12；沒有提供 Lab 1、2 或 12 之後的講義，因此不自行補造那些題目。
- 2024 題目內容以該年份講義為準；如 Review 僅含解題提示而沒有完整判題介面，各題 README 會列出採用的輸入輸出及資料限制。
- 原有重複、試玩、故障版本整合為每題一份正式程式；編譯產物不納入版本控制。
- 各 lab README 記錄題目限制、修正內容、使用方式與資料不足之處。講義 PDF 本身未納入此 repo。

Lab 6.1 的除錯模板使用固定寬度整數，但講義宣告的輸入上限會產生遠超出其表示能力的階乘。正式版本保留模板流程並明確檢查溢位，另提供大數延伸版本；細節及實際可用範圍見 `lab06/README.md`。

2024 的 Review 沒有提供所有原始 OJ 題目。特別是 Lab 7.3 的 almost-prime 定義、Lab 7.4 的 key 排程與輪數公式，會直接影響答案：7.3 明示採用的定義並附其他定義的編譯模式；7.4 實作講義的運算部件，以明確設定驅動完整流程。這些是可測試的參考實作，未宣稱已符合缺少的原題判題規格；請看 `2024/lab07/README.md` 及 `2024/lab07/FEISTEL_SPEC.md`。

2021 部分以提供的原始程式為基礎修訂；2024 部分依不同題目獨立實作。此 repo 沒有另行宣稱原始程式或課程材料的授權。
