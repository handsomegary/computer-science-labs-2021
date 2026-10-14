# 計算機概論實習：2021 與 2024

依國立中央大學 EE1007「Introduction to Computer Science Laboratory」各年份自己的課程講義整理。2021 以提供的原始程式碼補完與修正；2024 依該年份不同的題目實作。本 repo 保存獨立 C++11 程式、使用說明、自動測試、38 份官方 PDF 原檔，以及可取得的課程 starter／sample 附件；[來源附件核對](COMPANION_FILES.md)區分原樣保存、隨機匿名替代與未提供的官方原附件。

## 使用

| 年份 | 位置 | 題目範圍 |
| --- | --- | --- |
| 2021 | 根目錄 `lab01` 到 `lab14` | Lab 1–14，共 47 題，另有 Lab 6.1 大數延伸版 |
| 2024 | `2024/lab03` 到 `2024/lab12` | Lab 3–12，共 40 題重建題目、完整 solution 與可執行程式 |
| 2021 考古 | `exams/2021/midterm`、`exams/2021/final` | 期中 6 題、期末 7 題，共 13 題完整題目與 solution |

年份相同的題號也可能對應不同題目，請先選年份，再看各目錄的 README。每個 `labX_Y.cpp` 都有自己的 `main`，請逐題編譯，不要將多個作業一起連結。需依學校繳交規定命名時，可把該題檔案改為指定的「學號_姓名_LabX.Y.cpp」。2021 Lab 1.2 的姓名、學校與學號使用占位文字，可依繳交需求自行填寫。

考古題由 **[期中／期末完整題目與 solution 索引](exams/SOLUTIONS.md)** 進入；每頁包含完整程式碼，亦可取得 [JSON 題目集](exams/problems.json)。

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

所有需要檔案的正式程式都已有可直接使用的範例，並非只在測試時私下產生：

| 題目 | 已上傳的範例 | 執行方式 |
| --- | --- | --- |
| 2021 Lab 12.1–12.3 | [`lab12/1_1.txt`](lab12/1_1.txt)、[`2_1.txt`](lab12/2_1.txt)、[`3_1.txt`](lab12/3_1.txt) | 從 `lab12` 執行，按提示輸入對應檔名；12.3 先選 7 載入 |
| 2021 Lab 12.4 | [`lab12/4_1.txt`](lab12/4_1.txt) | 程式固定讀取 `4_1.txt`，必須從 `lab12` 執行 |
| 2021 Lab 13.3、14.3 | [`lab13/3_1.txt`](lab13/3_1.txt)、[`lab14/3_1.txt`](lab14/3_1.txt) | 從對應 lab 目錄執行，選 7，再輸入 `3_1.txt` |
| 2021 期末 C、G | [股票／會員 fixtures](exams/2021/final/fixtures) | 從 repo 根目錄執行時輸入 fixture 完整相對路徑，見[可直接照做的例子](exams/2021/final/README.md#直接使用已附的檔案範例) |

其餘正式程式從 stdin 取得數字、字串、矩陣或互動選單輸入，沒有未上傳的圖片、資料庫或專用資料檔相依性。Lab 12.2 產生的 `*out.txt` 是結果，不是啟動所需檔案。

## 自動驗證

測試僅依賴 Python 標準函式庫與 C++ 編譯器，執行檔放在暫存目錄，結束後刪除。

```sh
python tools/verify.py --cxx g++
python tools/check_course_materials.py
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
- 各 lab README 記錄題目限制、修正內容、使用方式與資料不足之處。官方 PDF 原檔已保存於 `originals/2021/`、`originals/2024/`，附件與 SHA256 見 [course-materials.json](course-materials.json)。

原始課程附件另在 `course_support/2021/`：六份 starter／template、原成績／禮物／字母盤檔案（含 `1_2.txt`、`2_2.txt`）皆按原始位元組保存。會員檔及其 ZIP 含個人欄位，使用 random names 與合成資料替代，明確標 `original_private_data_replaced`；不將它們稱為原版。

2024 P113019 的完整官方除錯 source，以及 P113042 的完整官方 template，在提供資料中沒有找到；目前只有投影片片段與 repo 的重建完成版。這兩項原教材缺口記為 `not_provided`，詳見 [COMPANION_FILES.md](COMPANION_FILES.md)，不能把「成品能執行」說成「全部原課程附件已保留」。

Lab 6.1 的除錯模板使用固定寬度整數，但講義宣告的輸入上限會產生遠超出其表示能力的階乘。正式版本保留模板流程並明確檢查溢位，另提供大數延伸版本；細節及實際可用範圍見 `lab06/README.md`。

2024 的 Review 未提供的題意與介面，依使用者要求已從詳解程式碼補定成完整練習題。講義明確規則與本次補定內容分開註明，統一標為重建版而非教授原題。每頁 solution 包含題解核心片段、解法與完整 C++11 程式碼，並由 CI 直接編譯內嵌程式、核對實測範例。請從 **[2024 題目與 solution 索引](2024/SOLUTIONS.md)** 開始。

2021 部分以提供的原始程式為基礎修訂；2024 部分依不同題目獨立實作。此 repo 沒有另行宣稱原始程式或課程材料的授權。
