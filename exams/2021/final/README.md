# 2021 期末考：完整題目與題解

本目錄依2021期末考卷重新實作，完整題面、範例及可編譯程式都在各題 `solutions/*.md` 中。資料只包含一般題目、匿名文字及股票數列，沒有個人作答者資料、原始考卷或截圖。

| 題目 | 程式 | 完整題目與題解 |
| --- | --- | --- |
| A：Spiral Graph II | [problem_a.cpp](problem_a.cpp) | [外擴螺旋](solutions/problem_a.md) |
| B：Build a Tree | [problem_b.cpp](problem_b.cpp) | [七節點搜尋樹與後序遍歷](solutions/problem_b.md) |
| C：Buy and Sell Stock | [problem_c.cpp](problem_c.cpp) | [檔案股票最大利潤](solutions/problem_c.md) |
| D：Is Anagram | [problem_d.cpp](problem_d.cpp) | [字母頻率重排](solutions/problem_d.md) |
| E：Encryption System | [problem_e.cpp](problem_e.cpp) | [指定類別交錯位移](solutions/problem_e.md) |
| F：Average Score II | [problem_f.cpp](problem_f.cpp) | [平均與不及格名單](solutions/problem_f.md) |
| G：Theater VII | [problem_g.cpp](problem_g.cpp) | [會員電話與完整訂位系統](solutions/problem_g.md) |

每題為獨立C++11程式，從repo根目錄編譯，例如：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic exams/2021/final/problem_a.cpp -o problem_a
```

Windows執行`problem_a.exe`，其他平台執行`./problem_a`。替換檔名即可編譯其他題。C題以工作目錄中的檔案讀取價格；兩份非個資資料在[fixtures/stock1.txt](fixtures/stock1.txt)及[fixtures/stock2.txt](fixtures/stock2.txt)。範例manifest內也附所需檔名與內容。

幾個考卷歧義已依正式範例及程式補齊：

- A的`width`為列數、`length`為欄數，螺旋可越界行走而不編號，並保持原本外擴轉彎位置。
- B必須為七個互異值，實際使用指定結構陣列與指標，後序遍歷不限平衡樹。
- C正式價格上限採考卷明文104；參考程式另支援帶符號32位元非負價格，以64位元累計利潤。
- E空格保持且仍占原索引，key²為9。資訊以位元組處理；公開範例已匿名化。空格保留與位移可能有符號碰撞，基本往返資料的界線明列於題面。
- F的N由所有分數至EOF推得；平均四捨五入至第二位並刪尾零，吻合40與47.5範例。70分及格。

從repo根目錄驗證A–F：

```sh
python tests/test_exam_2021_final.py --cxx g++
```

測試以無限螺旋的封閉座標公式、按根值分割的樹模型、買賣狀態動態規劃、字母頻率模型、獨立位元組轉換及Decimal平均比對，並重播完整範例。G使用訂位系統專用測試與整體驗證工具。
