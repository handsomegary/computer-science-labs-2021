# Lab 7.4：四位元組 Feistel 轉換（重建版）

本題依 2024 P113028 Review 的流程圖、`SWAP`／`SWITCH` 題解程式碼，以及本 repo 的完整解法重建。這是本 repo 正式定義的練習題，**不是教授原題的逐字還原**。題解程式碼是下方 solution 的一部分。

## 題目

設計一個以函式完成的四位元組資料轉換器。系統有四個 8-bit key，先依控制 key 交換指定的兩對位元，再將相鄰兩個 key 合成兩個 16-bit KEY。資料也由四個 byte 合成 16-bit 左半 `L` 與右半 `R`。

使用者明確提供每一輪的方向、KEY 與運算子。你必須依序完成所有轉換，再把左右半拆回四個 byte 輸出。不得使用陣列、vector 或 string 儲存 keys、資料或排程；排程逐輪讀入即可。

## 規則

所有位元編號均從最低位元 bit 0 起算。控制 key 為 `x`、被交換的 key 為 `y`：

1. 若 x 的 bit 4 為 1，交換 y 的 bit 7 與 bit 5。
2. 若 x 的 bit 3 為 1，交換 y 的 bit 2 與 bit 0。
3. 四個控制索引都指向**原始**四個 key，因此交換某個 key 不會影響其他交換的控制值。控制索引 -1 表示不交換。

交換後依序得 `k0'` 至 `k3'`，並設定：

```text
KEY1 = 256*k0' + k1'
KEY2 = 256*k2' + k3'
L = 256*byte0 + byte1
R = 256*byte2 + byte3
```

每輪 F 的編號與結果如下：

| F 編號 | `F(R,KEY)` |
| --- | --- |
| 0 | `R XOR KEY` |
| 1 | `R AND KEY` |
| 2 | `R OR KEY` |
| 3 | 高、低 byte 分別取餘數後整合：`256*((R/256)%(KEY/256)) + ((R%256)%(KEY%256))` |

E 表示正向輪：`(L,R) -> (R,L XOR F(R,KEY))`。D 表示反向輪：`(L,R) -> (R XOR F(L,KEY),L)`。因此 E 的一串排程若要解密，應以相反順序執行相同 KEY／F 的 D 輪；不得改成只反轉輸出的四個 byte。

F3 的 KEY 高或低 byte 為 0 時，輸出 `error` 並結束，不做除以零。其他 F 可使用零 key。

## 輸入

1. 四個十進位整數 `key0 key1 key2 key3`。
2. 四個控制索引 `control0 control1 control2 control3`，分別控制四個待交換的 key。
3. 資料行採以下其中一種格式：
   - `N byte0 byte1 byte2 byte3`：四個十進位 byte。
   - `T ` 後接正好四個原始 byte：T 後一個空白、換行或 tab 是分隔，其後四個字元不跳過空白。例如 `T A B!` 的資料是 A、空白、B、!。
4. 一個整數 n，表示接下來的輪數。
5. 接下來 n 筆 `direction KEY_index F_index`。direction 是 E 或 D；KEY_index 是 1 或 2；F_index 是 0–3。

數值欄位以空白或換行分隔。T 模式只有資料四個 byte 採原樣讀取。

## 輸出

N 模式輸出四個十進位 byte，以單一空白分隔並換行。T 模式輸出四個原始 byte，再換行；這是 byte 輸出，轉換後的值可能是不可列印字元。所有輸出不包含輸入回顯。

n 為 0 時保留資料。有效排程遇到 F3 的零除數時只輸出 `error`。

## 限制與補定來源

- key 與 N 模式的資料 byte 皆為 0–255；控制索引為 -1–3；每半資料與 KEY 為 16 bits。
- **本重建版的測資範圍**為 `0 <= n <= 100000`，用來確保串流轉換可在課堂時間內完成。程式的輪數儲存型別是有號 64 位元。
- 講義直接提供四個 8-bit key、16-bit 整合、位元交換及 F0–F3 的程式片段，這些規則均保留。
- 講義沒有給出完整控制排列、輪數生成公式與每輪排程。因此本重建題目補定為**全部由輸入明確指定**；不將自行想像的 generator 公式當成講義內容。
- D 輪、N／T 的確切介面、n 的實用上限與零除數診斷，是本重建版補定或擴充的完整規格。

## 範例

第一個範例的 KEY1 是 0x0102，輸入左右半是 0x0102、0x0304。F0 先計算 0x0304 XOR 0x0102；再與原左半 XOR 後得到 0x0304，因此輸出為 `3 4 3 4`。第二例執行同一 E 輪後再執行 D 輪，還原原資料。第三例以 0 輪驗證 T 模式保留中間空白。

<!-- SAMPLES_BEGIN -->
以下輸出是程式的標準輸出，包含提示；不包含終端機回顯的使用者輸入。

### 範例 1 輸入

```text
1 2 3 4
-1 -1 -1 -1
N 1 2 3 4
1
E 1 0
```

### 範例 1 輸出

```text
3 4 3 4
```

### 範例 2 輸入

```text
1 2 3 4
-1 -1 -1 -1
N 1 2 3 4
2
E 1 0
D 1 0
```

### 範例 2 輸出

```text
1 2 3 4
```

### 範例 3 輸入

```text
0 0 0 0
-1 -1 -1 -1
T A B!
0
```

### 範例 3 輸出

```text
A B!
```
<!-- SAMPLES_END -->

## solution

### 講義題解程式碼的核心

Review 的 `SWAP` 範例以十進位整數的 0／1 數字表示二進位字串。下面轉寫其可確認的交換規則，使用實際位元運算保存相同意思；這是完整解法中的 `scramble` 函式，不是只有題目中的示意圖：

```cpp
std::uint32_t scramble(std::uint32_t control, std::uint32_t value) {
    if (control & 16u) value = swap_bits(value, 7, 5);
    if (control & 8u) value = swap_bits(value, 2, 0);
    return value;
}
```

Review 的 `SWITCH` 範例提供 `R ^ KEY ^ L`、`(R & KEY) ^ L`、`(R | KEY) ^ L` 及逐 byte MOD 後再 XOR L。完整解法先把 F 與外層 XOR 分開，使正反輪共用同一個 F；MOD 的題解核心如下：

```cpp
const std::uint32_t high_divisor = key >> 8;
const std::uint32_t low_divisor = key & 255u;
if (high_divisor == 0 || low_divisor == 0) return false;
result = (((right >> 8) % high_divisor) << 8)
         | ((right & 255u) % low_divisor);
```

### 解題步驟與正確性

1. 讀入並驗證四個原始 key，用原 key 作控制來源，各自計算交換後的 key。
2. 左移 8 bits 並合併相鄰 bytes，得到兩個 KEY 及資料 L／R。
3. 逐輪讀排程，只保留目前的 L、R 和該輪設定，不需要排程陣列。
4. 正向輪保存舊 R，讓新 L 等於舊 R、新 R 等於舊 L XOR F(舊 R,KEY)。反向輪由相同 XOR 的自反性恢復舊 L、R。
5. 以右移 8 bits 和 `& 255` 拆回高低 byte，按選定模式輸出。

同一位元 XOR 同一值兩次會還原，故上面的 D 確為 E 的逆步驟。交換兩個位元也不改變 byte 的範圍。所有 F 和 XOR 結果仍在 16-bit 範圍，不需要把二進位位數先轉成很大的十進位整數。

時間複雜度 O(n)，除輸入串流外的額外空間 O(1)。完整 solution 只使用純量和函式，符合本題不得宣告 array、vector 或 string 的要求。

### 完整 C++11 solution 程式碼

以下程式碼由 `lab7_4.cpp` 同步嵌入，solution 本身包含完整可編譯程式。CI 會直接編譯這個區塊並核對上方所有範例。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2024 P113028: configurable reference implementation of the supplied diagrams.
// The Review omits the iteration-count and round-selection rules. Those values
// are explicit inputs here; FEISTEL_SPEC.md distinguishes them from lecture rules.
#include <cstdint>
#include <iostream>

std::uint32_t swap_bits(std::uint32_t value, unsigned first, unsigned second) {
    if (((value >> first) & 1u) != ((value >> second) & 1u))
        value ^= (1u << first) | (1u << second);
    return value;
}

std::uint32_t scramble(std::uint32_t control, std::uint32_t value) {
    // SWAP(x,y) in the slide: x.bit4 controls y.bit7 <-> y.bit5;
    // x.bit3 controls y.bit2 <-> y.bit0. Native bits preserve leading zeros.
    if (control & 16u) value = swap_bits(value, 7, 5);
    if (control & 8u) value = swap_bits(value, 2, 0);
    return value;
}

std::uint32_t select_key(int index, std::uint32_t key0, std::uint32_t key1,
                         std::uint32_t key2, std::uint32_t key3) {
    switch (index) {
        case 0: return key0;
        case 1: return key1;
        case 2: return key2;
        default: return key3;
    }
}

bool round_function(unsigned selector, std::uint32_t right,
                    std::uint32_t key, std::uint32_t& result) {
    switch (selector) {
        case 0: result = right ^ key; break;
        case 1: result = right & key; break;
        case 2: result = right | key; break;
        case 3: {
            // The slide's MOD applies separately to the two 8-bit halves.
            const std::uint32_t high_divisor = key >> 8;
            const std::uint32_t low_divisor = key & 255u;
            if (high_divisor == 0 || low_divisor == 0) return false;
            result = (((right >> 8) % high_divisor) << 8)
                     | ((right & 255u) % low_divisor);
            break;
        }
        default: return false;
    }
    return true;
}

bool feistel_round(std::uint32_t& left, std::uint32_t& right,
                   std::uint32_t key, unsigned selector, bool inverse) {
    std::uint32_t transformed;
    if (!round_function(selector, inverse ? left : right, key, transformed)) return false;
    if (inverse) {
        const std::uint32_t old_right = left;
        left = right ^ transformed;
        right = old_right;
    } else {
        const std::uint32_t old_right = right;
        right = left ^ transformed;
        left = old_right;
    }
    return true;
}

bool read_byte(std::uint32_t& value) {
    long long input;
    if (!(std::cin >> input) || input < 0 || input > 255) return false;
    value = static_cast<std::uint32_t>(input);
    return true;
}

int main() {
    std::uint32_t key0, key1, key2, key3;
    int control0, control1, control2, control3;
    if (!read_byte(key0) || !read_byte(key1) || !read_byte(key2) || !read_byte(key3)
        || !(std::cin >> control0 >> control1 >> control2 >> control3)
        || control0 < -1 || control0 > 3 || control1 < -1 || control1 > 3
        || control2 < -1 || control2 > 3 || control3 < -1 || control3 > 3) {
        std::cout << "error\n";
        return 1;
    }
    // All controls refer to the original input keys; -1 means no scrambling.
    const std::uint32_t scrambled0 = control0 == -1 ? key0
        : scramble(select_key(control0, key0, key1, key2, key3), key0);
    const std::uint32_t scrambled1 = control1 == -1 ? key1
        : scramble(select_key(control1, key0, key1, key2, key3), key1);
    const std::uint32_t scrambled2 = control2 == -1 ? key2
        : scramble(select_key(control2, key0, key1, key2, key3), key2);
    const std::uint32_t scrambled3 = control3 == -1 ? key3
        : scramble(select_key(control3, key0, key1, key2, key3), key3);
    const std::uint32_t KEY1 = (scrambled0 << 8) | scrambled1;
    const std::uint32_t KEY2 = (scrambled2 << 8) | scrambled3;

    char mode;
    std::uint32_t byte0, byte1, byte2, byte3;
    if (!(std::cin >> mode)) return 1;
    if (mode == 'N') {
        if (!read_byte(byte0) || !read_byte(byte1) || !read_byte(byte2) || !read_byte(byte3)) {
            std::cout << "error\n";
            return 1;
        }
    } else if (mode == 'T') {
        // Exactly one delimiter follows T; the next four raw bytes are the text.
        char delimiter, char0, char1, char2, char3;
        if (!std::cin.get(delimiter) || (delimiter != ' ' && delimiter != '\n' && delimiter != '\t')
            || !std::cin.get(char0) || !std::cin.get(char1)
            || !std::cin.get(char2) || !std::cin.get(char3)) {
            std::cout << "error\n";
            return 1;
        }
        byte0 = static_cast<unsigned char>(char0);
        byte1 = static_cast<unsigned char>(char1);
        byte2 = static_cast<unsigned char>(char2);
        byte3 = static_cast<unsigned char>(char3);
    } else {
        std::cout << "error\n";
        return 1;
    }
    std::uint32_t left = (byte0 << 8) | byte1;
    std::uint32_t right = (byte2 << 8) | byte3;
    long long rounds;
    if (!(std::cin >> rounds) || rounds < 0) {
        std::cout << "error\n";
        return 1;
    }
    for (long long i = 0; i < rounds; ++i) {
        char direction;
        int key_index;
        long long selector;
        if (!(std::cin >> direction >> key_index >> selector)
            || (direction != 'E' && direction != 'D')
            || (key_index != 1 && key_index != 2)
            || selector < 0 || selector > 3
            || !feistel_round(left, right, key_index == 1 ? KEY1 : KEY2,
                              static_cast<unsigned>(selector), direction == 'D')) {
            std::cout << "error\n";
            return 1;
        }
    }
    if (mode == 'N') {
        std::cout << (left >> 8) << ' ' << (left & 255u) << ' '
                  << (right >> 8) << ' ' << (right & 255u) << '\n';
    } else {
        std::cout << static_cast<char>(left >> 8) << static_cast<char>(left & 255u)
                  << static_cast<char>(right >> 8) << static_cast<char>(right & 255u) << '\n';
    }
    return 0;
}
```
<!-- SOLUTION_CODE_END -->
