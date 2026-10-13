# 2024 Lab 5.4：Monopoly Game：矩形路線雙人遊戲

本文件是依 2024 Review 圖碼及現有 C++11 題解重建的完整題目，**不是教授原題的逐字稿**。本 repository 的作答與驗證以以下明確規格為準；講義依據與補定規則分別列出。

## 題目

矩形路線高H、寬W，一圈長L=2(H+W−2)。A、B初始位置0、分數100；每輪A先、B後各移動1–6格。落在三個非起點轉角H−1、H+W−2、2H+W−3時，立即後退2格，只處理一次、不重複触发新轉角。超過終點L就停在L。未到終點時按重複序列字元加扣分。任何人到終點仍完成另一人的當輪移動，再結束；總分高者獲勝，同分平手。

## 輸入格式

第一行輸入整數H、W；行內其餘內容不使用。下一整行輸入序列S，長度1–8，只包含`.`、`a`–`z`、`A`–`Z`，行尾必須有換行。其後依輪次輸入A、B的步數，數值以空白或換行分隔。非法序列重讀一整行；非法步數重讀同一玩家步數。正常測资最終須有人到終點並且分數保持64位範圍。

## 輸出格式

先印 `Enter height and width: ` 與 `Enter Sequence: `，都不換行；序列不合法印 `Out of the bound. Enter again.` 與換行，再印序列提示。游戏開始印一個換行，再印 `Start Game!`；每輪開始再印換行，接著依序印不換行的 `A move: `、`B move: `。非法步數印 `Out of the bound. Enter again.` 與換行，重印該玩家提示。

每輪最後印 `A and B are at position PA and PB` 與換行、`A and B have score SA and SB` 與換行。結局為 `Player A wins the game!`、`Player B wins the game!` 或 `The two players are tied!`，加換行。尺寸非法時stderr印 `This interface supports dimensions from 3 to 2147483647.` 與換行並回傳1；游戏未完成遇EOF正常退出，不印伪造勝負。

## 限制與邊界

3 <= H,W <= 2147483647；1 <= |S| <= 8，S不含空格；每次有效步數1–6。位置、L、分數採用long long。序列第一個字元對應位置1，第|S|個對應位置|S|；落回0時也按周期對應最後字元。`.`不加扣，`a`–`z`加1–26，`A`–`Z`扣1–26。終點不加扣分。CR字元忽略；用cin.get與八個char儲存，不以陣列或string取代。

## 解法說明

用while控制完整兩人輪次；for處理A、B各一次。更新位置後先判轉角、截断終點；仍在路線內才用((position+length−1)%length)+1選擇序列字元並加扣分。每輪记录兩人的位置與分數，結束後以scoreA/scoreB比較勝負。讀取序列O(|S|)，每輪O(1)，額外空間O(1)。

## 講義可確認的規則

Review P113020 明確提供cin.get、八個char、L公式、初始位置0與分數100、完整A/B輪次、1–6步數及越界字串、三個轉角退2、終點截断、重複序列對位、大小寫加扣與三種結局訊息。

## 重建版自行補定的規則

尺寸範圍3–2147483647與其提示、序列長度/字元的驗證、按最終分數决定勝負與不重複触发轉角，都以現有程式明確為重建版規則。此題不是教授原題逐字稿；採用Review偽碼的完整當輪語義，而不是A到終點就取消B的步數。

## 範例與說明

範例1為最小3×3路線，L=8，轉角2、4、6。A第一步2退到0，仍依重複序列a加1；完成後兩人都是102分，因此平手。範例2使用a.Bz確認大小寫獎懲，A最終126分、B98分，A獲勝；到終點的當輪仍讀取B步數。

下列完整 stdout 是實際程式輸出，不含終端機輸入回顯；沒有換行的提示會與下一段輸出接在同一行。每個範例均從全新程序開始。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
3 3
a
2
1
6
6
6
6
```

### 範例 1 輸出

```text
Enter height and width: Enter Sequence: 
Start Game!
A move: B move: A and B are at position 0 and 1
A and B have score 101 and 101

A move: B move: A and B are at position 4 and 7
A and B have score 102 and 102

A move: B move: A and B are at position 8 and 8
A and B have score 102 and 102
The two players are tied!
```

### 範例 2 輸入

```text
6 7
a.Bz
6
1
6
6
6
6
6
6
```

### 範例 2 輸出

```text
Enter height and width: Enter Sequence: 
Start Game!
A move: B move: A and B are at position 6 and 1
A and B have score 100 and 101

A move: B move: A and B are at position 12 and 7
A and B have score 126 and 99

A move: B move: A and B are at position 18 and 13
A and B have score 126 and 100

A move: B move: A and B are at position 22 and 19
A and B have score 126 and 98
Player A wins the game!
```
<!-- SAMPLES_END -->

## 題解核心程式片段

下列為現有 repository 修訂解法的核心節錄，已將 Review 可確認的方向融入實作；不是聲稱教授提供此完整片段。節錄省略輸入驗證或周邊列印，完整可編譯版本見下節。

```cpp
position += steps;
if (position == height - 1 || position == height + width - 2
    || position == 2 * height + width - 3) position -= 2;
if (position > route) position = route;
if (position < route) {
    const int index = static_cast<int>((position + length - 1) % length + 1);
    // switch(index) 從八個char中取得symbol。
    if (symbol >= 'a' && symbol <= 'z') score += symbol - 'a' + 1;
    else if (symbol >= 'A' && symbol <= 'Z') score -= symbol - 'A' + 1;
}
```

## 完整題解程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
#include <iostream>
#include <limits>

int main()
{
    long long height = 0, width = 0;
    std::cout << "Enter height and width: ";
    if (!(std::cin >> height >> width) || height < 3 || width < 3
        || height > 2147483647LL || width > 2147483647LL) {
        std::cerr << "This interface supports dimensions from 3 to 2147483647.\n";
        return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    char seq1 = '.', seq2 = '.', seq3 = '.', seq4 = '.';
    char seq5 = '.', seq6 = '.', seq7 = '.', seq8 = '.';
    int length = 0;
    bool valid = false;
    do {
        std::cout << "Enter Sequence: ";
        length = 0;
        valid = true;
        char symbol = 0;
        while (std::cin.get(symbol) && symbol != '\n') {
            if (symbol == '\r') continue;
            if (length <= 8) ++length;
            if (symbol != '.' && !(symbol >= 'a' && symbol <= 'z')
                && !(symbol >= 'A' && symbol <= 'Z')) valid = false;
            switch (length) {
            case 1: seq1 = symbol; break;
            case 2: seq2 = symbol; break;
            case 3: seq3 = symbol; break;
            case 4: seq4 = symbol; break;
            case 5: seq5 = symbol; break;
            case 6: seq6 = symbol; break;
            case 7: seq7 = symbol; break;
            case 8: seq8 = symbol; break;
            default: valid = false; break;
            }
        }
        if (!std::cin) return 0;
        if (length == 0 || length > 8) valid = false;
        if (!valid) std::cout << "Out of the bound. Enter again.\n";
    } while (!valid);

    const long long route = 2 * (height + width - 2);
    long long positionA = 0, positionB = 0;
    long long scoreA = 100, scoreB = 100;
    std::cout << "\nStart Game!";
    while (positionA < route && positionB < route) {
        std::cout << '\n';
        // The Review completes both A and B's turn before ending a round.
        for (int player = 0; player < 2; ++player) {
            int steps = 0;
            bool accepted = false;
            do {
                std::cout << (player == 0 ? "A move: " : "B move: ");
                if (std::cin >> steps) {
                    accepted = steps >= 1 && steps <= 6;
                } else {
                    if (std::cin.eof()) return 0;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                if (!accepted) std::cout << "Out of the bound. Enter again.\n";
            } while (!accepted);
            long long position = player == 0 ? positionA : positionB;
            long long score = player == 0 ? scoreA : scoreB;
            position += steps;
            if (position == height - 1 || position == height + width - 2
                || position == 2 * height + width - 3) position -= 2;
            if (position > route) position = route;
            if (position < route) {
                const int index = static_cast<int>((position + length - 1) % length + 1);
                char symbol = '.';
                switch (index) {
                case 1: symbol = seq1; break;
                case 2: symbol = seq2; break;
                case 3: symbol = seq3; break;
                case 4: symbol = seq4; break;
                case 5: symbol = seq5; break;
                case 6: symbol = seq6; break;
                case 7: symbol = seq7; break;
                case 8: symbol = seq8; break;
                }
                if (symbol >= 'a' && symbol <= 'z') score += symbol - 'a' + 1;
                else if (symbol >= 'A' && symbol <= 'Z') score -= symbol - 'A' + 1;
            }
            if (player == 0) { positionA = position; scoreA = score; }
            else { positionB = position; scoreB = score; }
        }
        std::cout << "A and B are at position " << positionA << " and " << positionB << '\n'
                  << "A and B have score " << scoreA << " and " << scoreB << '\n';
    }
    if (scoreA > scoreB) std::cout << "Player A wins the game!\n";
    else if (scoreB > scoreA) std::cout << "Player B wins the game!\n";
    else std::cout << "The two players are tied!\n";
    return 0;
}
```
<!-- SOLUTION_CODE_END -->

## 編譯與執行

在 `2024/lab05` 執行：

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic lab5_4.cpp -o lab5_4
./lab5_4
```

Windows PowerShell 執行 `./lab5_4.exe`。完整原始碼為 [`lab5_4.cpp`](../lab5_4.cpp)；機器可驗證範例在本目錄 `samples.json`。
