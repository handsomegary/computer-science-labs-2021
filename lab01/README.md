# 2021 Lab 1：第一支程式

本目錄根據 2021 Lab 1 講義與提供的原始作業整理；身分欄位使用占位文字。每個 `.cpp` 都是獨立程式，使用 C++11。

| 檔案 | 完成內容 |
| --- | --- |
| `lab1_1.cpp` | 分兩行輸出 `Hello` 與小寫的 `world!`。 |
| `lab1_2.cpp` | 輸出姓名、學校、學號的占位文字、課程問候與可辨認的 NCU 星號圖形。 |

在此目錄執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab1_1.cpp -o lab1_1
./lab1_1
g++ -std=c++11 -Wall -Wextra -Wpedantic lab1_2.cpp -o lab1_2
./lab1_2
```

Windows PowerShell 的執行命令為 `./lab1_1.exe`、`./lab1_2.exe`。Lab 1.2 的身分欄位採 ASCII 占位文字；原始碼統一使用 UTF-8。

修正原作 `Hello` 後方多餘空白、`World!` 的大小寫、`studetn` 拼字與不一致換行；將原作 Big5 中文轉為 UTF-8。依題目要求，Lab 1.2 未使用 `using namespace std;`，雙引號、反斜線與單引號都有保留。姓名、學校與學號改用 `<NAME>`、`<SCHOOL>`、`<STUDENT_ID>` 占位文字，未保留個人資料。

講義的 Lab 1.1 還要求自行操作 Code::Blocks 並提交執行畫面截圖；本 repository 提供可編譯程式，未冒充完成課堂 demo 或截圖繳交。測試涵蓋兩支程式的輸出、跳脫字元與 NCU 圖形行寬。
