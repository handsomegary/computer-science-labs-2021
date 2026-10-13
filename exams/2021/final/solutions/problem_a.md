# 2021 期末 A：Spiral Graph II：外擴螺旋

> 完整重建版，非考卷逐字抄錄。已知規則與範例依2021期末考卷；歧義與缺漏以本頁明訂規則補齊。程式為獨立重新實作，公開內容只使用非個資範例。

## 題目

建立 width 列、length 欄的矩形，在座標 (x,y) 放入 1，再依順時針、向外擴大的螺旋順序填入遞增整數。x 是列、y 是欄，座標從 0 起算。第一方向向右，直線段長度依序為 1、1、2、2、3、3、…，方向為右、下、左、上循環。螺旋可以走到矩形外；越界位置只消耗移動步數，不填入數字，不改變轉彎時機。返回矩形內的未填格才放下一個數字，直到每格都填滿。這與考卷圖中越界的紅色虛線及兩個範例相符。

## 輸入

單筆四個整數 width、length、x、y，以空白或換行分隔。也可原樣貼上範例中的 `Width,Length`、`x,y` 標籤；程式只忽略這兩個完整 token，不印出標籤。

## 輸出

只輸出 width 行，每行 length 個整數，各數以一個空格分隔，行尾無空格，最後換行。每格補零至 width×length 的十進位位數。維度、起點或讀取格式無效時印 `error` 並回傳 1。

## 限制與邊界

3≤width,length≤31；0≤x<width，0≤y<length。考卷另列 x,y≤30，重建版補上必須位於目前矩形內。最大數為961，使用固定31×31陣列。

## 範例

stdout只包含程式輸出，不含終端機回顯的輸入。以下輸出已由C++11編譯後實際捕捉。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 輸入

```text
Width,Length
4 5
x,y
1 3
```

### 範例 1 輸出

```text
20 16 07 08 09
19 15 06 01 02
18 14 05 04 03
17 13 12 11 10
```

### 範例 2 輸入

```text
10 22
0 21
```

### 範例 2 輸出

```text
220 210 200 190 180 170 160 150 140 130 120 110 100 081 064 049 036 025 016 009 004 001
219 209 199 189 179 169 159 149 139 129 119 109 099 080 063 048 035 024 015 008 003 002
218 208 198 188 178 168 158 148 138 128 118 108 098 079 062 047 034 023 014 007 006 005
217 207 197 187 177 167 157 147 137 127 117 107 097 078 061 046 033 022 013 012 011 010
216 206 196 186 176 166 156 146 136 126 116 106 096 077 060 045 032 021 020 019 018 017
215 205 195 185 175 165 155 145 135 125 115 105 095 076 059 044 031 030 029 028 027 026
214 204 194 184 174 164 154 144 134 124 114 104 094 075 058 043 042 041 040 039 038 037
213 203 193 183 173 163 153 143 133 123 113 103 093 074 057 056 055 054 053 052 051 050
212 202 192 182 172 162 152 142 132 122 112 102 092 073 072 071 070 069 068 067 066 065
211 201 191 181 171 161 151 141 131 121 111 101 091 090 089 088 087 086 085 084 083 082
```
<!-- SAMPLES_END -->

範例說明：第一例從(1,3)先向右到2、下到3，再向左到4、5。外圈暫時越界後在底列填10–13，最左欄依序填17–20。第二例起點在右上角；首次越界的步數不占數字，所以右上是001，右下是082。

## 解法

保留矩形外的目前座標，按兩個等長直線段增加段長。只有座標合法且值為0時填入下一數字。不能一碰邊界就提前轉向，否則會卡在已填格而與正式範例不符。最大外擴距離至多30，整段模擬至多覆蓋約61×61的位置；時間O(max(width,length)²)，儲存矩形為O(width×length)。

## 考卷已知與重建補定

考卷已知：考卷給出順時針外擴、不重訪、矩形邊界、補零及兩個正式範例；圖示明確容許在矩形外繼續行走。

重建補定：明訂width為列、length為欄、起點需位於矩形、首次向右與1,1,2,2段長、可忽略範例標籤、非法輸入的error，以及無提示／無行尾空格。

## 完整題解程式

獨立來源：[../problem_a.cpp](../problem_a.cpp)。

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2021 final A: an expanding clockwise spiral, clipped to the rectangle.
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool readInteger(int& number) {
    string token;
    while (cin >> token) {
        if (token == "Width,Length" || token == "x,y") continue;
        istringstream input(token);
        return static_cast<bool>(input >> number) && input.peek() == char_traits<char>::eof();
    }
    return false;
}
int main() {
    int rows, columns, row, column;
    if (!readInteger(rows) || !readInteger(columns) || !readInteger(row) || !readInteger(column) ||
        rows < 3 || rows > 31 || columns < 3 || columns > 31 || row < 0 || row >= rows ||
        column < 0 || column >= columns) { cout << "error\n"; return 1; }
    int graph[31][31] = {};
    const int dr[4] = {0, 1, 0, -1}, dc[4] = {1, 0, -1, 0};
    const int total = rows * columns;
    int value = 1, direction = 0, distance = 1;
    graph[row][column] = value++;
    while (value <= total) {
        // Segment lengths 1,1,2,2,3,3,...; off-grid positions consume steps,
        // but do not consume sequence numbers or change the spiral geometry.
        for (int segment = 0; segment < 2 && value <= total; ++segment) {
            for (int step = 0; step < distance && value <= total; ++step) {
                row += dr[direction];
                column += dc[direction];
                if (row >= 0 && row < rows && column >= 0 && column < columns && graph[row][column] == 0)
                    graph[row][column] = value++;
            }
            direction = (direction + 1) % 4;
        }
        ++distance;
    }
    const int digits = total < 10 ? 1 : total < 100 ? 2 : 3;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (c) cout << ' ';
            cout << setfill('0') << setw(digits) << graph[r][c];
        }
        cout << '\n';
    }
}
```
<!-- SOLUTION_CODE_END -->
