# 2024 Lab 6.3　P113023：電器行優惠券

> 重建版，非教授原題。本題面依提供的 2024 講義／詳解提示與本 repo 現有程式重建；下方明確區分可確認的講義內容及補定規則。

## 題目

建立可反覆服務顧客的 NCU 電器行系統。每次詢問是否進店，再詢問是否持有會員卡及消費額，依下表發給優惠。選擇離店後結束程式。必須使用 `enterStore()`、`hasMembershipCard()`、`calculateRewards(bool, int)` 三個函式。

| 會員 | 消費金額 | 優惠 |
| --- | --- | --- |
| 有 | <5000 | 500 元優惠券 |
| 有 | 5000–10000 | 1000 元優惠券 |
| 有 | >10000 | 3000 元優惠券及一張彩券 |
| 無 | <7000 | 無優惠 |
| 無 | 7000–10000 | 500 元優惠券 |
| 無 | >10000 | 1500 元優惠券並成為會員 |

## 輸入

一次服務的輸入依序為進店 Y/N、會員 Y/N、非負整數消費額。Y/y 表示是，N/n 表示否。每次發放優惠後回到進店問題；進店問題回答 N/n 即結束，無須再提供會員或金額。其他 Y/N 選擇會重試；消費額讀取失敗或為負數時重試。各次顧客的會員狀態重新輸入，不保存上一位顧客的狀態。

## 輸出

每輪先印商店抬頭與進店提示；進店時再印會員及消費提示，最後印一行獎勵。明確回答 N/n 離店時印 GOOD BYE 行。EOF 正常結束，不補印離店訊息。完整英文提示及獎勵字串以本頁範例和完整題解為準，提示文字不包含終端機自行回顯的使用者輸入。

## 限制

消費額在 0–2147483647。輸入由 Y/N token 與整數組成；每次重試非法數值時，可用一行提交新金額。獎勵的 5000、7000、10000 邊界必須依表判斷。

## 範例

以下 stdout 為編譯現有程式後捕捉的完整輸出，包含提示的空白與換行；輸入回顯不是 stdout。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
y
y
5000
n
```

### 範例 1 輸出

```text
*** NCU Electrical Appliance Store ***
Do you want to go inside or leave the store(Y/N): Do you have the membership card(Y/N): Enter the money you spent: ***Congratulations !! You get 1000 dollars coupon!!
*** NCU Electrical Appliance Store ***
Do you want to go inside or leave the store(Y/N): ************************ GOOD BYE! *************************
```
<!-- SAMPLES_END -->

範例說明：第一輪進店且持有會員卡，花費 5000，取得 1000 元優惠券。下一輪回答 n，印離店訊息。

## 解法與核心程式

三個函式分別處理進店、會員狀態與優惠，`main` 控制重複服務。先依會員分支，再依兩個金額界線分類，避免把 10000 誤歸入最高優惠。每次服務的計算時間與額外空間均為 O(1)。

以下為目前題解的核心片段，使用的輔助函式、型別與完整主程式列於完整題解。

```cpp
void calculateRewards(bool hasMembership, int spending) {
    if (hasMembership) {
        if (spending < 5000)
            cout << "***Congratulations !! You get 500 dollars coupon!!\n";
        else if (spending <= 10000)
            cout << "***Congratulations !! You get 1000 dollars coupon!!\n";
        else
            cout << "***Congratulations !! You get 3000 dollars coupon and one lottery ticket!!\n";
    } else {
        if (spending < 7000)
            cout << "***Oh no!! You do not have any bonus to get...\n";
        else if (spending <= 10000)
            cout << "***Congratulations !! You get 500 dollars coupon!!\n";
        else
            cout << "***Congratulations !! You get 1500 dollars coupon and become a store member!!\n";
    }
}
```

## 講義內容與重建補定

講義已知：講義流程圖、三個指定函式與提示、六種獎勵字串、會員／金額界線均可從圖片確認；`main` 片段以 `break` 離開重複服務。

自行補定：消費額提示 `Enter the money you spent:`、非法選擇重試、EOF 行為、完整迴圈及不保存上次會員狀態由重建版補定。

## 完整題解程式

完整可編譯版本：[../lab6_3.cpp](../lab6_3.cpp)。下列程式碼區與該原始碼同步。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113023: prompts and coupon brackets are transcribed from the slides.
#include <iostream>
#include <limits>
#include <string>
using namespace std;

bool enterStore() {
    string choice;
    cout << "*** NCU Electrical Appliance Store ***\n"
         << "Do you want to go inside or leave the store(Y/N): ";
    while (cin >> choice) {
        if (choice == "Y" || choice == "y") return true;
        if (choice == "N" || choice == "n") return false;
        cout << "Invalid input, please enter Y or N: ";
    }
    return false;
}
bool hasMembershipCard() {
    string choice;
    cout << "Do you have the membership card(Y/N): ";
    while (cin >> choice) {
        if (choice == "Y" || choice == "y") return true;
        if (choice == "N" || choice == "n") return false;
        cout << "Invalid input, please enter Y or N: ";
    }
    return false;
}
void calculateRewards(bool hasMembership, int spending) {
    if (hasMembership) {
        if (spending < 5000)
            cout << "***Congratulations !! You get 500 dollars coupon!!\n";
        else if (spending <= 10000)
            cout << "***Congratulations !! You get 1000 dollars coupon!!\n";
        else
            cout << "***Congratulations !! You get 3000 dollars coupon and one lottery ticket!!\n";
    } else {
        if (spending < 7000)
            cout << "***Oh no!! You do not have any bonus to get...\n";
        else if (spending <= 10000)
            cout << "***Congratulations !! You get 500 dollars coupon!!\n";
        else
            cout << "***Congratulations !! You get 1500 dollars coupon and become a store member!!\n";
    }
}
int main() {
    while (true) {
        if (!enterStore()) {
            if (cin) cout << "************************ GOOD BYE! *************************\n";
            return 0;
        }
        const bool member = hasMembershipCard();
        if (!cin) return 0;
        int spending;
        cout << "Enter the money you spent: ";
        while (true) {
            if (cin >> spending) {
                if (spending >= 0) break;
            } else {
                if (cin.eof()) return 0;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Invalid spending, please enter again: ";
        }
        calculateRewards(member, spending);
    }
}
```
<!-- SOLUTION_CODE_END -->
