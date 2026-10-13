# 2024 Lab 7.4：Feistel Cipher 參考實作

`lab7_4.cpp` 完成提供的 Review 中可確認的 Key Scrambler、Key Integrator、XOR／AND／OR／MOD 算子、Feistel round、輸入與輸出整合。依題目限制，全程使用純量與函式，不宣告 array、vector 或 string。

## 講義已明確給出的部分

- 四個 key，各 8 bits；整合成兩個 16-bit KEY。
- 四個資料 byte，整合成 16-bit 左半與右半。
- 圖示 `SWAP(x,y)`：x 的 bit 4 為 1 時交換 y 的 bit 7 與 bit 5；x 的 bit 3 為 1 時交換 y 的 bit 2 與 bit 0。
- F0 = XOR、F1 = AND、F2 = OR、F3 = MOD。
- MOD 依投影片的 `SWITCH` 範例，對右半與 KEY 的高、低 byte 分別取餘數，再整合並與原左半 XOR。
- 每輪使用 `(L,R) -> (R,L XOR F(R,KEY))`；程式也提供該步驟的反向運算。

## Review 沒有提供的部分

投影片未列出每個 key 由哪個 key 控制的完整排列、Iteration Time Generator 如何產生輪數、每輪選哪個 KEY／key'／F，以及原題的完整輸入輸出範例。因此這份程式把這些值作為**明確設定輸入**，不假造原課程的排程公式，也不宣稱它已符合未取得的 HydroOJ P113028 原題介面。

目前可用它驗證講義的運算部件及自行指定的完整加解密流程。取得原題之後，運算函式可保留，再將 `main` 的設定讀取換成原題的 key 排程與輪數公式。

## 可執行介面

1. 輸入四個 key：`key0 key1 key2 key3`，各為 0–255。
2. 輸入四個控制索引：`control0 control1 control2 control3`。-1 表示不交換；0–3 指向原輸入的控制 key。交換全部依原始 keys 執行。
3. 資料行：`N byte0 byte1 byte2 byte3`，或 `T ` 後接正好四個原始字元。T 後一個空白、換行或 tab 為分隔，後四個 byte 不跳過空白。
4. 輪數 n。
5. n 筆 `E/D KEY_index F_index`：E 為正向，D 為反向，KEY_index 為 1 或 2，F_index 為 0、1、2、3。解密時以逆序提供原先的排程，方向設 D。

輸出為四個十進位 byte（N）或四個原始 byte（T），最後換行。MOD 的任一 KEY byte 為 0 時回報 `error`，避免除以零。純量參數出界或不完整輸入也會回傳非零狀態。

例如原始 KEY1 為 0x0102、資料為 0x01020304，一輪 XOR：

```text
1 2 3 4
-1 -1 -1 -1
N 1 2 3 4
1
E 1 0
```

結果為 `3 4 3 4`。用同一個 KEY／F 做反向輪，可還原 `1 2 3 4`。0 輪保留輸入。

repo 根目錄編譯及驗證：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic 2024/lab07/lab7_4.cpp -o y2024_lab7_4
python tests/test_2024_lab7_4.py --cxx g++
```
