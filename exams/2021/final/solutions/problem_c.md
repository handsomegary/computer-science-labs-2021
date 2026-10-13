# 2021 期末 C：Buy and Sell Stock：不限交易次數的最大利潤

> 完整重建版，非考卷逐字抄錄。已知規則與範例依2021期末考卷；歧義與缺漏以本頁明訂規則補齊。程式為獨立重新實作，公開內容只使用非個資範例。

## 題目

讀取股票價格檔案，計算能取得的最大總利潤。每天可買進或賣出，交易次數不限，但任一時刻至多持有一股；當天買進後立刻賣出也可以。價格依天數排列，不可回到過去交易，不可放空，也沒有手續費。沒有能獲利的交易時答案為0。

## 輸入

stdin是一整行檔名，可含中間空白。檔案第一行為非空股票名稱，第二行為`prices:`及至少一個整數價格，以空白分隔。檔名相對於程式工作目錄。合法檔案只含這兩行；參考程式只解析前兩行，不將後續行納入價格。

## 輸出

先印`File: `且不換行。成功時印`Maximum profit: P`及換行；使用者的檔名回顯不屬於stdout，所以範例捕捉輸出是`File: Maximum profit: 7`同一行。找不到檔案印`Cannot open file.`；格式、價格或筆數無效印`Invalid stock data.`，這些錯誤回傳1。

## 限制與邊界

正式限制按現有考卷明文採1–312筆、價格0–104。文字`104`沒有上標；若原排版原意為10⁴，現有解法仍可處理。作為額外數值擴充，參考程式接受0–2147483647的價格、利潤用64位元整數；這不改正式測資限制。

## 範例

stdout只包含程式輸出，不含終端機回顯的輸入。以下輸出已由C++11編譯後實際捕捉。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 附件 `stock1.txt`

```text
stock1
prices: 7 1 5 3 6 4
```

### 範例 1 輸入

```text
stock1.txt
```

### 範例 1 輸出

```text
File: Maximum profit: 7
```

### 範例 2 附件 `stock2.txt`

```text
stock2
prices: 1 2 3 4 5 6 7 8 9 10
```

### 範例 2 輸入

```text
stock2.txt
```

### 範例 2 輸出

```text
File: Maximum profit: 9
```
<!-- SAMPLES_END -->

範例說明：stock1買1賣5得4，再買3賣6得3，總利潤7。stock2一路上升，可買1賣10得9；分段每日交易總額也相同。範例所需檔案內容隨samples.json提供，並有fixtures副本。

## 解法

每一段上升路徑的谷底買、峰頂賣，利潤等於該段所有正相鄰差值總和。不同上升段之間不持股，符合至多一股限制。累加max(0,prices[i]-prices[i-1])即可。時間O(N)，保存價格空間O(N)。索引從1掃到N-1，避免讀取不存在的最後一日。

## 考卷已知與重建補定

考卷已知：考卷明定檔案前兩行、交易不限、至多一股、同日可交易、無獲利輸出0，以及stock1最大利潤7。

重建補定：嚴格`prices:`標籤、單行完整檔名、檔案錯誤訊息、只解析前兩行、64位元擴充與數值範圍。對模糊數字採明文104，未把它暗改成10⁴。

## 完整題解程式

獨立來源：[../problem_c.cpp](../problem_c.cpp)。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2021 final C: unlimited transactions, with at most one share held.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

long long maximumProfit(const vector<long long>& prices) {
    long long profit = 0;
    for (size_t i = 1; i < prices.size(); ++i)
        if (prices[i] > prices[i - 1]) profit += prices[i] - prices[i - 1];
    return profit;
}
int main() {
    string filename;
    cout << "File: ";
    if (!getline(cin, filename)) return 1;
    if (!filename.empty() && filename.back() == '\r') filename.pop_back();
    ifstream file(filename.c_str());
    if (!file) { cout << "Cannot open file.\n"; return 1; }
    string name, line, label;
    if (!getline(file, name) || !getline(file, line) || name.empty()) {
        cout << "Invalid stock data.\n";
        return 1;
    }
    istringstream input(line);
    if (!(input >> label) || label != "prices:") { cout << "Invalid stock data.\n"; return 1; }
    vector<long long> prices;
    string token;
    while (input >> token) {
        istringstream parser(token);
        long long price;
        if (!(parser >> price) || parser.peek() != char_traits<char>::eof() ||
            price < 0 || price > 2147483647LL || prices.size() == 312) {
            cout << "Invalid stock data.\n";
            return 1;
        }
        prices.push_back(price);
    }
    if (!input.eof() || prices.empty()) { cout << "Invalid stock data.\n"; return 1; }
    cout << "Maximum profit: " << maximumProfit(prices) << '\n';
}
```
<!-- SOLUTION_CODE_END -->
