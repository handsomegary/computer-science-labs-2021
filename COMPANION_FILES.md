# 原講義與搭配附件核對

完整原始檔清單、來源檔名、SHA256、PDF 引用頁及對應附件見 [course-materials.json](course-materials.json)。本次保存 38 份官方 PDF 原檔：[2021 共 27 份](originals/2021)、[2024 共 11 份](originals/2024)。包含作業題面、Review、除錯／OJ／操作說明；沒有學生報告或個人提交截圖。PDF、非個資文字檔及六份 starter／template 保留原始位元組與檔名。

這份核對分別檢查「目前成品程式可執行」與「原講義要求的附件是否保存」。現有成品程式可完整執行，仍有下列兩份 2024 官方原始 starter 在提供資料中缺少，不能以重寫的完整解答冒充原檔。

## 2021 來源附件

| 講義引用 | 已保存檔案 | 保存狀態 |
| --- | --- | --- |
| Lab 6 PDF 第 1 頁：給定含八個錯誤的 `.cpp` | [lab6_1err original one.cpp](course_support/2021/templates/lab6_1err%20original%20one.cpp) | 原樣保存；它本來就是故障除錯題，並非完成版 |
| Lab 7 PDF 第 3 頁：`LAB7_2_sample.cpp` | [原名 LAB7_2_smaple.cpp](course_support/2021/templates/LAB7_2_smaple.cpp)、[題面拼字別名](course_support/2021/templates/LAB7_2_sample.cpp) | 原提供檔拼字為 `smaple`；兩份內容完全相同 |
| Lab 7 PDF 第 5 頁：`LAB7_3_sample.cpp` | [LAB7_3_sample.cpp](course_support/2021/templates/LAB7_3_sample.cpp) | 原樣保存 |
| Lab 12 PDF 第 3 頁：`Lab12_2_sample.cpp` | [Lab12_2_sample.cpp](course_support/2021/templates/Lab12_2_sample.cpp) | 原樣保存 |
| Lab 13 更新版 PDF 第 3 頁：血型 sample code | [sample_code_13_2.cpp](course_support/2021/templates/sample_code_13_2.cpp) | 原樣保存，保留原未完成宣告 |
| Lab 14 PDF 第 10 頁：`reverse_str` 指定 class | [Lab14.4_template.cpp](course_support/2021/templates/Lab14.4_template.cpp) | 原樣保存，與投影片 class 介面對應 |
| Lab 12 PDF 第 2、4、10 頁：成績、禮物、字母盤 | [1_1.txt](course_support/2021/lab12/examples/1_1.txt)、[2_1.txt](course_support/2021/lab12/examples/2_1.txt)、[4_1.txt](course_support/2021/lab12/examples/4_1.txt) | 原樣保存，包含原換行與空白 |
| 本機課程集合另外提供的替代案例 | [1_2.txt](course_support/2021/lab12/examples/1_2.txt)、[2_2.txt](course_support/2021/lab12/examples/2_2.txt) | 原樣保存；不將它們說成題面明示的附件檔名 |
| Lab 12、13、14 PDF 的會員檔欄位 | [Lab 12 的 3_1.txt／3_2.txt](course_support/2021/lab12/examples)、[電話欄位版本 3_1.txt](course_support/2021/lab14/examples/3_1.txt) | `original_private_data_replaced`；random names、合成密碼／電話，保留各原檔筆數與欄位 |
| 本機提供的 Theater VI 會員資料包 | [53 NCU Theater Reservation System(VI).zip](originals/anonymized_resources/53%20NCU%20Theater%20Reservation%20System%28VI%29.zip) | `original_private_data_replaced`；原 ZIP 只有 `3_1.txt`，保存同名 archive/member 結構，內容使用匿名替代；不是原始位元組 |

六份模板各在五個提供的課程原始碼集合中找到相同 SHA256。它們保留原本的空白函式、故障程式或未完成 class，方便依課程原流程練習；正式可執行解答仍在 `labXX/`。模板不加入正式 CMake targets。

`2_1out.txt` 是 Lab 12.2 應產生的結果，並非缺少的必要輸入。來源集合裡有不同學生操作產生的輸出檔，不把這些個人結果當成官方附件。本 repo 的完整程式會依選擇的禮物產生輸出。

匿名會員檔使用隨機代稱；相同來源帳號／密碼在不同例檔保持對應，電話改為合成數字。Manifest 記錄原 SHA256、替代 SHA256、筆數及欄位，沒有公開原會員內容，也不把 synthetic sample 標成 original。

## 2024 來源缺口

11 份 2024 PDF 共 137 頁已核對文字及程式圖片。未發現外部 TXT、ZIP、圖片、音效或自訂函式庫的具名供應附件；一般程式畫面、測試數量、Code::Blocks／gdb 路徑及演算法網頁分別記錄為內嵌例子、評分說明或外部工具參考。

| 題目 | 原說明證據 | 官方原附件狀態 | Repo 的完成版 |
| --- | --- | --- | --- |
| P113019／Lab 5.3 Debugging | [Lab 5 Review](originals/2024/2024Fall_EE1007_CSLab_Lab5_Review_20241024.pdf) 第 10 頁明示提供完整 source；11–14 頁只見局部修正畫面 | `not_provided`：本機沒有可確認的官方未修改 starter；不把已修學生程式當原始題目 | [lab5_3.cpp](2024/lab05/lab5_3.cpp)，依可見規則重建 |
| P113042／Lab 12.2 Digital Root | [Lab 12](originals/2024/2024Fall_EE1007_CSLab_Lab12_20241216.pdf) 第 5 頁要求只改 `CODE BEGIN/END`；第 7 頁只有片段，且 pointer／reference 介面互相矛盾 | `not_provided`：本機沒有完整官方 template，不能宣稱圖片片段就是完整原檔 | [lab12_2.cpp](2024/lab12/lab12_2.cpp)，依明訂 pointer 介面重建 |

兩項缺口都列在 Manifest 的 `missing_original_companions`。成品範例可執行，不等於原始受限改寫題目的所有 source template 已取得。之後若提供原檔，可直接以 SHA256 及題目引用位置補入；目前不自行重造「官方原檔」。

## 下載後核對保存檔案

只需要 Python 標準函式庫：

```sh
python tools/check_course_materials.py
python tools/check_course_materials.py --json
```

此工具核對所有 PDF、starter、文字範例及匿名 ZIP 的存在、SHA256、別名／ZIP 結構與引用對應；缺檔或內容變動會失敗，GitHub CI 也執行同一檢查。結果另外明示 `original_course_attachment_set_complete: false` 及兩項已知來源缺口，不把保存檔案的 hash 通過當成原附件全集完整。

若需要嚴格要求原附件全集完整，使用 `python tools/check_course_materials.py --require-complete`；目前會因兩份 2024 原 source 未提供而回傳 2。
