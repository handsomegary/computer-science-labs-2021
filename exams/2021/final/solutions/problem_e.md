# 2021 期末 E：Encryption System：交錯位移

> 完整重建版，非考卷逐字抄錄。已知規則與範例依2021期末考卷；歧義與缺漏以本頁明訂規則補齊。程式為獨立重新實作，公開內容只使用非個資範例。

## 題目

實作指定的encrypt類別，包含encrypt(string)建構子、encryption()、decryption()、print_information()三個public方法，以及private string information和int key=3。字串以0-based位元組索引逐字處理：偶數位置加key²=9，奇數位置減key=3。解密做相反位移。依正式範例，ASCII空格本身保持不變，但仍占索引位置，不能把字串拆詞重組。

## 輸入

第一行為1（加密）或2（解密），第二行為完整資訊，可為空行；前後及連續空格都保留。模式後至換行的其餘字元忽略。換行不屬於資訊；末尾CR作為CRLF的一部分移除。基本明文字元為ASCII32–126，合法解密資料由上述加密產生。

## 輸出

先印三行歡迎／模式選項，接著空一行，再印`Input information: `且不換行。結果接著印`Encrypted information: `或`Decrypted information: `與轉換後字串，最後換行。無法讀取模式或模式不為1/2時印error並回傳1；缺少資訊行時保留提示後回傳1。範例以匿名文字轉寫，不附個人姓名。

## 限制與邊界

本題沒有另設字串長度上限，以可配置的string為限。不是Unicode字元位移，而是8-bit位元組運算；非空格位移按mod256保存，某些結果可能超出可列印ASCII。空格是保留符號，因此基本往返測資另排除「奇數索引的#」，它減3會變成空格而與原空格混淆。此限制由重建版明訂；對限制外資料仍按字面位移，不承諾唯一還原。

## 範例

stdout只包含程式輸出，不含終端機回顯的輸入。以下輸出已由C++11編譯後實際捕捉。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
1
Test is a good message
```

### 範例 1 輸出

```text
Welcome to encryption system!
Enter 1 to encrypt
Enter 2 to decrypt

Input information: Encrypted information: ]b|q f| j plxa jnp|^pb
```

### 範例 2 輸入

```text
2
]b|q f| j plxa jnp|^pb
```

### 範例 2 輸出

```text
Welcome to encryption system!
Enter 1 to encrypt
Enter 2 to decrypt

Input information: Decrypted information: Test is a good message
```
<!-- SAMPLES_END -->

範例說明：匿名範例保持正式加解密的提示與演算法。索引0的T加9變成]，索引1的e減3變成b。各空格不變；同一索引的解密做逆操作，還原原文。

## 解法

建構子保存整行資訊。兩個方法依原索引取unsigned char值，分別加/減9或3，再轉回一個位元組；不處理ASCII空格。完整getline保留所有空白，避免逐詞讀入丟失索引。時間O(L)，information儲存O(L)，原地轉換額外空間O(1)。

## 考卷已知與重建補定

考卷已知：考卷指定類別欄位／介面、key3、模2交錯規則、模式1/2與提示；正式範例證明空格保持但仍占位置，key²指平方而非C++ XOR。

重建補定：明訂0-based索引、完整行輸入、空字串、末尾CR、位元組模256、不可唯一還原的空格碰撞測資界線與錯誤處理。公開範例匿名化，不複製個人資訊。

## 完整題解程式

獨立來源：[../problem_e.cpp](../problem_e.cpp)。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2021 final E: the prescribed encrypt class, with spaces preserved.
#include <iostream>
#include <limits>
#include <string>
using namespace std;

class encrypt {
public:
    explicit encrypt(string text) : information(text) {}
    void encryption() {
        for (size_t i = 0; i < information.size(); ++i) {
            if (information[i] == ' ') continue;
            const int value = static_cast<unsigned char>(information[i]);
            const int changed = i % 2 == 0 ? value + key * key : value - key;
            information[i] = static_cast<char>(static_cast<unsigned char>(changed));
        }
    }
    void decryption() {
        for (size_t i = 0; i < information.size(); ++i) {
            if (information[i] == ' ') continue;
            const int value = static_cast<unsigned char>(information[i]);
            const int changed = i % 2 == 0 ? value - key * key : value + key;
            information[i] = static_cast<char>(static_cast<unsigned char>(changed));
        }
    }
    void print_information() { cout << information << '\n'; }
private:
    string information;
    int key = 3;
};
int main() {
    cout << "Welcome to encryption system!\nEnter 1 to encrypt\nEnter 2 to decrypt\n";
    int mode;
    if (!(cin >> mode) || (mode != 1 && mode != 2)) { cout << "error\n"; return 1; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nInput information: ";
    string information;
    if (!getline(cin, information)) return 1;
    if (!information.empty() && information.back() == '\r') information.pop_back();
    encrypt message(information);
    if (mode == 1) { message.encryption(); cout << "Encrypted information: "; }
    else { message.decryption(); cout << "Decrypted information: "; }
    message.print_information();
}
```
<!-- SOLUTION_CODE_END -->
