# 2024 Lab 4.4：Banking System：存提款與單利借還款

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

實作銀行互動選單。初始餘額為 0、未還本金為 0。存款增加餘額；提款僅在餘額足夠時扣除；借款增加餘額並留下本金；還款依借款年數計算 5% 年單利，只有一次付清才扣餘額並清除本金。一次最多一筆未還借款。所有選單功能以 switch 實作。

## 輸入格式

反覆讀整數選項：1 存款、2 提款、3 借款、4 還款、5 離開。1、2 各再讀一個正金額；3 在沒有未還借款時再讀正金額，已有借款時不讀金額。4 在沒有借款時不讀年數，已有借款時再讀非負整數年數 Y。所有數值以空白或換行分隔。

## 輸出格式

每輪依序印五行 `1. Deposit`、`2. Withdraw`、`3. Borrow`、`4. Repay`、`5. Exit`，再印不換行的 `Enter your selection: `。非法選項印 `Invalid selection.` 與換行。5 直接結束，不印告別詞。

1、2、3 的金額提示分別為 `Enter the deposit amount: `、`Enter the withdrawal amount: `、`Enter the loan amount: `。非法金額以 `Invalid amount. Enter again: ` 重試。存款、成功提款、成功借款印 `Current balance: $B` 與換行；提款不足印 `Insufficient balance to withdraw.`；再次借款印 `Repay the outstanding loan before borrowing again.`。兩個失敗訊息皆加換行。

4 先印 `Current balance: $B` 與換行。無本金印 `No outstanding loan to repay.`；有本金印不換行的 `Enter the number of years since the loan: `，非法年數以 `Invalid duration. Enter again: ` 重試。接著印 `Total amount to repay: $R` 與換行。足額印 `Repayment successful.` 與換行、`Balance after repayment: $B` 與換行；不足印 `Insufficient balance to repay the loan.` 與換行。

所有金額固定顯示兩位小數。存款／借款使餘額超出有限 double 時印 `Amount is outside the supported numeric range.` 與換行，不改狀態。互動 EOF 正常結束；文字讀取失敗清除該行。

## 限制與邊界

金額為有限 double 且 > 0；年數為 0–2147483647。餘額與本金使用 double，不在每次操作後取整；餘額不得負值。應還額 R = P + P×0.05×Y，為單利而非複利。應還額若超出有限值，視為無法足額還款，保留本金。

## 解法說明

switch 分派功能。還款先檢查是否有本金；取得年數後計算 totalRepay，只有 balance >= totalRepay 且結果有限才更新 balance、loanAmount。失敗不變更兩個狀態，避免誤將未還貸款清零。時間 O(操作及重試次數)，額外空間 O(1)。

## 講義可確認的規則

Review 明確列五種功能、switch 目標、5% 年單利，並提供還款提示、貸款為零、成功清除本金、餘額不足的完整片段。

## 重建版自行補定的規則

初始餘額 0、選單 1–5、一次只能一筆本金、只能全額還款、非負整年、正金額、兩位小數與精確訊息已補定為本題規格，不標作教授原題。

## 範例與說明

借 100 後餘額 100，再存 10 變成 110。借款一年應還 100 + 100×0.05 = 105，還款後剩 5。本金清零後才能再借款；年數 0 的邊界只需還本金。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
3
100
1
10
4
1
5
```

### 範例 1 輸出

```text
1. Deposit
2. Withdraw
3. Borrow
4. Repay
5. Exit
Enter your selection: Enter the loan amount: Current balance: $100.00
1. Deposit
2. Withdraw
3. Borrow
4. Repay
5. Exit
Enter your selection: Enter the deposit amount: Current balance: $110.00
1. Deposit
2. Withdraw
3. Borrow
4. Repay
5. Exit
Enter your selection: Current balance: $110.00
Enter the number of years since the loan: Total amount to repay: $105.00
Repayment successful.
Balance after repayment: $5.00
1. Deposit
2. Withdraw
3. Borrow
4. Repay
5. Exit
Enter your selection: 
```

此範例的標準輸出最後沒有換行；code fence 的結束行只用於排版。
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
const double totalRepay = loanAmount + loanAmount * interestRate * years;
if (balance >= totalRepay && std::isfinite(totalRepay)) {
    balance -= totalRepay;
    loanAmount = 0.0;
    std::cout << "Repayment successful.\n";
} else {
    std::cout << "Insufficient balance to repay the loan.\n";
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// The Review omits the initial balance and menu numbering; see README.
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

bool readAmount(double& amount)
{
    while (true) {
        if (std::cin >> amount) {
            if (std::isfinite(amount) && amount > 0.0) {
                return true;
            }
        } else {
            if (std::cin.eof()) {
                return false;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Invalid amount. Enter again: ";
    }
}

int main()
{
    const int DEPOSIT = 1, WITHDRAW = 2, BORROW = 3, REPAY = 4, EXIT = 5;
    double balance = 0.0;
    double loanAmount = 0.0;
    const double interestRate = 0.05;
    std::cout << std::fixed << std::setprecision(2);
    while (true) {
        std::cout << "1. Deposit\n2. Withdraw\n3. Borrow\n4. Repay\n5. Exit\nEnter your selection: ";
        int choice = 0;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid selection.\n";
            continue;
        }
        double amount = 0.0;
        switch (choice) {
        case DEPOSIT:
            std::cout << "Enter the deposit amount: ";
            if (!readAmount(amount)) return 0;
            if (!std::isfinite(balance + amount)) {
                std::cout << "Amount is outside the supported numeric range.\n";
                break;
            }
            balance += amount;
            std::cout << "Current balance: $" << balance << '\n';
            break;
        case WITHDRAW:
            std::cout << "Enter the withdrawal amount: ";
            if (!readAmount(amount)) return 0;
            if (amount > balance) {
                std::cout << "Insufficient balance to withdraw.\n";
            } else {
                balance -= amount;
                std::cout << "Current balance: $" << balance << '\n';
            }
            break;
        case BORROW:
            // A single outstanding loan makes its duration unambiguous.
            if (loanAmount > 0.0) {
                std::cout << "Repay the outstanding loan before borrowing again.\n";
                break;
            }
            std::cout << "Enter the loan amount: ";
            if (!readAmount(amount)) return 0;
            if (!std::isfinite(balance + amount)) {
                std::cout << "Amount is outside the supported numeric range.\n";
                break;
            }
            loanAmount = amount;
            balance += amount;
            std::cout << "Current balance: $" << balance << '\n';
            break;
        case REPAY: {
            std::cout << "Current balance: $" << balance << '\n';
            if (loanAmount == 0.0) {
                std::cout << "No outstanding loan to repay.\n";
                break;
            }
            std::cout << "Enter the number of years since the loan: ";
            int years = 0;
            while (!(std::cin >> years) || years < 0) {
                if (std::cin.eof()) return 0;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid duration. Enter again: ";
            }
            const double totalRepay = loanAmount + loanAmount * interestRate * years;
            std::cout << "Total amount to repay: $" << totalRepay << '\n';
            if (balance >= totalRepay && std::isfinite(totalRepay)) {
                balance -= totalRepay;
                loanAmount = 0.0;
                std::cout << "Repayment successful.\nBalance after repayment: $" << balance << '\n';
            } else {
                std::cout << "Insufficient balance to repay the loan.\n";
            }
            break;
        }
        case EXIT:
            return 0;
        default:
            std::cout << "Invalid selection.\n";
            break;
        }
    }
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab04` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab4_4.cpp -o lab4_4
./lab4_4
```

Windows PowerShell 執行 `./lab4_4.exe`。完整原始碼為 [`lab4_4.cpp`](../lab4_4.cpp)；機器可驗證範例在本目錄 `samples.json`。
