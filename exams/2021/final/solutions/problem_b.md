# 2021 期末 B：Build a Tree：七節點搜尋樹

> 完整重建版，非考卷逐字抄錄。已知規則與範例依2021期末考卷；歧義與缺漏以本頁明訂規則補齊。程式為獨立重新實作，公開內容只使用非個資範例。

## 題目

依輸入順序將七個互異整數建成二元搜尋樹。第一個數是根節點；新值比目前節點小時往左，比目前節點大時往右，在第一個空子指標處接上新節點。最後依左子樹、右子樹、根節點的後序順序輸出所有值。必須使用具有num、left、right的node結構及恰好七個元素的node陣列；先逐一存入數值，再連接指標。

## 輸入

恰好七個互異十進位整數，以空白或換行分隔。

## 輸出

七個後序遍歷數值，同一行以單一空格隔開，沒有行尾空格，最後換行。數值超範圍、缺少輸入或重複值時印error並回傳1。

## 限制與邊界

每個值在-2147483648至2147483647。考卷規定左值嚴格小於、右值嚴格大於，因此重建版明訂七個值互異；不可用固定平衡樹位置或排序後陣列冒充指標樹。

## 範例

stdout只包含程式輸出，不含終端機回顯的輸入。以下輸出已由C++11編譯後實際捕捉。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
26 17 41 14 21 30 47
```

### 範例 1 輸出

```text
14 21 17 30 47 41 26
```

### 範例 2 輸入

```text
1 2 3 4 5 6 7
```

### 範例 2 輸出

```text
7 6 5 4 3 2 1
```
<!-- SAMPLES_END -->

範例說明：第一例左右子樹分別輸出14 21 17與30 47 41，最後根26。第二例逐次向右形成一條鏈，後序從最深的7一路回到1。

## 解法

七個node陣列元素持有實際節點，插入時沿left/right指標查找空位。遞迴後序先處理左右，再印目前節點；bool first控制空格。建樹最壞O(7²)，遍歷O(7)，節點與遞迴堆疊最多七個。

## 考卷已知與重建補定

考卷已知：考卷指定node結構、七元素陣列、首值為根、左右大小規則；紅色遍歷編號及兩個範例確認後序。

重建補定：將未說明的重複值明訂為錯誤，補上讀取錯誤處理及精確空格格式。節點不另行動態配置。

## 完整題解程式

獨立來源：[../problem_b.cpp](../problem_b.cpp)。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2021 final B: the prescribed seven-element node array and postorder traversal.
#include <cstdint>
#include <iostream>
using namespace std;

struct node {
    int num;
    node *left = nullptr;
    node *right = nullptr;
};
void insert(node *root, node *item) {
    while (true) {
        node **child = item->num < root->num ? &root->left : &root->right;
        if (*child == nullptr) { *child = item; return; }
        root = *child;
    }
}
void postorder(const node *root, bool& first) {
    if (root == nullptr) return;
    postorder(root->left, first);
    postorder(root->right, first);
    if (!first) cout << ' ';
    cout << root->num;
    first = false;
}
int main() {
    node nodes[7];
    for (int i = 0; i < 7; ++i) {
        int64_t value;
        if (!(cin >> value) || value < -2147483648LL || value > 2147483647LL) {
            cout << "error\n";
            return 1;
        }
        nodes[i].num = static_cast<int>(value);
        for (int j = 0; j < i; ++j) if (nodes[j].num == nodes[i].num) {
            cout << "error\n";
            return 1;
        }
    }
    for (int i = 1; i < 7; ++i) insert(&nodes[0], &nodes[i]);
    bool first = true;
    postorder(&nodes[0], first);
    cout << '\n';
}
```
<!-- SOLUTION_CODE_END -->
