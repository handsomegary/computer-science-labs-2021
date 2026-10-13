# 2021 期末 G：NCU Theater Reservation System VII

依提供的正式考卷整理。下方 solution 包含完整、可獨立編譯的 C++11 解答。範例會員均為合成資料。

## 題目

延續課堂的劇院訂位系統，保留訂位、取消、查詢座位、會員註冊與登入、載入會員、修改資料及關鍵字搜尋功能。修改 `show_member`，同時顯示所有會員的使用者名稱與電話。電話必須保存為字串，保留開頭的 0。

預設表頭為 `No.  Username    Phone`：`No.` 後兩個空格，`Username` 後四個空格。編號欄寬為 5；使用者名稱從 U 所在欄開始，所有電話從 P 所在欄開始。

## 輸入

程式持續讀取主選單命令。每個互動欄位依提示輸入；選單與座位編號是整數，y/n 欄位採小寫，文字欄位各占一行。

| 命令 | 後續輸入 | 行為 |
| --- | --- | --- |
| 1 | y/n；y 時再輸入座位編號 | 指定空位或自動選最小空位 |
| 2 | 座位編號 | 取消該座位 |
| 3 | 無 | 依序顯示空位 |
| 4 | 無 | 顯示全部座位狀態 |
| 5 | 未登入：y/n，依流程再給名稱、密碼、電話 | 會員中心；登入後同命令登出 |
| 6 | 無 | 顯示會員名稱與電話 |
| 7 | 檔名 | 載入會員資料 |
| 8 | 1/2、名稱、舊密碼、新密碼或新電話 | 通過驗證後修改資料 |
| 9 | 搜尋字串 | 依名稱搜尋，大小寫相異；列出符合會員 |
| 10 | 無 | 結束 |

座位為 1–15，最多 15 位會員。名稱與密碼各為 1–50 個字元。電話保存輸入原字串。文字的開頭空白由互動讀取略過，中間空白保留。

命令 7 的文字檔每筆為 `username password phone`，以空白分隔；第一個非空白行可為 `Name Password Phone` 表頭。檔案欄位不得包含空白。程式從執行工作目錄尋找相對路徑，範例附件必須先建立。

## 輸出

每輪列出完整英文主選單與 `Enter your selection Here: ` 提示，無輸入回顯。登入後顯示歡迎文字，命令 5 改列登出。命令 10 顯示 `Thank you for using our system`、`Have a nice day~~` 各一行。

命令 6 先印 `***NCU Theater Membership***`。沒有會員時印 `No Member`；有會員時印表頭，再以載入或註冊順序列出編號、名稱、電話。密碼不出現在會員清單中。

## 原題規則與採用的邊界行為

考卷直接要求會員電話、表頭空格、U/P 欄對齊，以及保留課堂功能。本解答沿用 repo 既有劇院系統流程與 15 個座位／會員限制。

- 名稱最多 10 字元時，表頭完全符合考卷空格規則。課堂文字欄位可達 50 字元；較長名稱時，本版將名稱欄擴大到「最長名稱長度 + 2」，同時移動表頭 Phone 與所有電話欄，避免文字互相覆蓋。這是長名稱的明確擴充規則。
- 重複註冊名稱不新增會員。檔案的重複名稱、錯誤欄數、超長名稱／密碼或超過 15 位會員，整次載入輸出 `Invalid member data.`，不部分更新名單。這是本版明確補定的檔案錯誤行為。
- 找不到檔案時印 `File could not be opened.`。非法選單／座位／y/n 會重讀；指定已保留座位時要求再選。EOF 結束程式，不完成尚未讀完的註冊、訂位或資料修改。
- 紀錄只存在程式執行期間，離開後不另寫會員檔案。

## 範例

第一例先載入三筆合成會員資料，再顯示清單並離開；電話前導 0 與表頭對齊均需保留。第二例顯示初始空名單。

<!-- SAMPLES_BEGIN -->
下列是實際 stdin／stdout，包含程式提示，不包含使用者輸入的終端機回顯。

### 範例 1 附件 `member1.txt`

```text
Name Password Phone
GuestA demoA 0000000001
GuestB demoB 0000000002
GuestLong demoC 0000000003
```

### 範例 1 輸入

```text
7
member1.txt
6
10
```

### 範例 1 輸出

```text
*** Welcome to NCU theater reservation system ***
Please type 1 to make a new reservation
Please type 2 to cancel an existing reservation
Please type 3 to show the all available seats
Please type 4 to show the status of all current seats
Please type 5 to member center
Please type 6 to show member
Please type 7 to load member information
Please type 8 to change member data
Please type 9 to find member data
Please type 10 to exit the system
Enter your selection Here: 
***Load member information***
Please enter the member file name: The file member1.txt has been loaded...

*** Welcome to NCU theater reservation system ***
Please type 1 to make a new reservation
Please type 2 to cancel an existing reservation
Please type 3 to show the all available seats
Please type 4 to show the status of all current seats
Please type 5 to member center
Please type 6 to show member
Please type 7 to load member information
Please type 8 to change member data
Please type 9 to find member data
Please type 10 to exit the system
Enter your selection Here: 
***NCU Theater Membership***
No.  Username    Phone
1.   GuestA      0000000001
2.   GuestB      0000000002
3.   GuestLong   0000000003

*** Welcome to NCU theater reservation system ***
Please type 1 to make a new reservation
Please type 2 to cancel an existing reservation
Please type 3 to show the all available seats
Please type 4 to show the status of all current seats
Please type 5 to member center
Please type 6 to show member
Please type 7 to load member information
Please type 8 to change member data
Please type 9 to find member data
Please type 10 to exit the system
Enter your selection Here: 
Thank you for using our system
Have a nice day~~
```

### 範例 2 輸入

```text
6
10
```

### 範例 2 輸出

```text
*** Welcome to NCU theater reservation system ***
Please type 1 to make a new reservation
Please type 2 to cancel an existing reservation
Please type 3 to show the all available seats
Please type 4 to show the status of all current seats
Please type 5 to member center
Please type 6 to show member
Please type 7 to load member information
Please type 8 to change member data
Please type 9 to find member data
Please type 10 to exit the system
Enter your selection Here: 
***NCU Theater Membership***
No Member

*** Welcome to NCU theater reservation system ***
Please type 1 to make a new reservation
Please type 2 to cancel an existing reservation
Please type 3 to show the all available seats
Please type 4 to show the status of all current seats
Please type 5 to member center
Please type 6 to show member
Please type 7 to load member information
Please type 8 to change member data
Please type 9 to find member data
Please type 10 to exit the system
Enter your selection Here: 
Thank you for using our system
Have a nice day~~
```
<!-- SAMPLES_END -->

## solution

### 解法

用 15 格布林陣列儲存座位狀態，會員資料用結構與 vector 儲存，登入狀態保存會員索引。`show_member` 先決定名稱欄寬，再使用 `std::left`、`std::setw` 輸出表頭與各列；編號加句點後填滿 5 欄，兩位數編號仍與 U 對齊。會員電話使用 string，避免失去前導 0。

載入時先把所有新資料放進暫存 vector，核對欄數、長度、重複名稱及容量，整份合法才加入現有名單。因此錯誤檔案不會留下半套資料，也不會改變登入中的索引。訂位、取消與會員驗證分別使用對應函式，主選單只負責派送。

若本次檔案有 r 筆資料、已存在 m 位會員，載入檢查為 O(r(m+r))；m+r 最多 15。會員清單為 O(m+文字總長)，座位操作掃描固定 15 格。除會員文字與一行檔案緩衝外，空間為 O(m+r)。

### 完整 C++11 程式碼

<!-- SOLUTION_CODE_BEGIN -->
```cpp
// 2021 final exam G: preserve theater features and display member phones.
// This translation unit is self-contained: submit or compile this .cpp alone.
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct MemberData { string username, password, phone; };
struct Theater {
    bool reserved[15];
    vector<MemberData> members;
    int logged_in;
    Theater() : reserved{}, logged_in(-1) {}
};
const char *invalid_input = "Invalid input, please enter your selection again: ";

bool read_integer(int& value, int minimum, int maximum) {
    string token;
    while (cin >> token) {
        istringstream parser(token);
        char extra;
        if (parser >> value && !(parser >> extra) && value >= minimum && value <= maximum) return true;
        cout << invalid_input;
    }
    return false;
}
bool read_yes_no(char& answer) {
    string token;
    while (cin >> token) {
        if (token == "y" || token == "n") { answer = token[0]; return true; }
        cout << invalid_input;
    }
    return false;
}
bool read_text(string& value, bool limited = true) {
    while (getline(cin >> ws, value)) {
        if (!value.empty() && (!limited || value.size() <= 50)) return true;
        cout << invalid_input;
    }
    return false;
}
int authenticate(const Theater& theater, const string& username, const string& password) {
    for (size_t i = 0; i < theater.members.size(); ++i)
        if (theater.members[i].username == username && theater.members[i].password == password)
            return static_cast<int>(i);
    return -1;
}
void Member(Theater& theater) {
    cout << "***NCU Theater Member Center***\nDo you have the membership? (y/n) ";
    char answer;
    if (!read_yes_no(answer)) return;
    if (answer == 'y') {
        string username, password;
        cout << "Enter Username: ";
        if (!read_text(username)) return;
        cout << "Enter Password: ";
        if (!read_text(password)) return;
        theater.logged_in = authenticate(theater, username, password);
        if (theater.logged_in == -1) cout << "The username and the password don't match.\n";
    } else {
        cout << "Would you like to sign up? (y/n) ";
        if (!read_yes_no(answer)) return;
        if (answer == 'n') { cout << "Okay! Have a nice day.\n"; return; }
        if (theater.members.size() >= 15) { cout << "The member center is full.\n"; return; }
        MemberData member;
        cout << "Enter Username: ";
        if (!read_text(member.username)) return;
        cout << "Enter Password: ";
        if (!read_text(member.password)) return;
        cout << "Enter Phone number: ";
        if (!read_text(member.phone, false)) return;
        for (size_t i = 0; i < theater.members.size(); ++i)
            if (theater.members[i].username == member.username) {
                cout << "This username already exists.\n";
                return;
            }
        theater.members.push_back(member);
        cout << "Welcome! You are now a member of NCU theater.\nPlease log in again.\n";
    }
}
void reserve_seat(Theater& theater) {
    cout << "***Make a new reservation***\n";
    int first_available = -1;
    for (int i = 0; i < 15; ++i)
        if (!theater.reserved[i]) { first_available = i; break; }
    if (first_available == -1) { cout << "All seats have been reserved.\n"; return; }
    cout << "Do you need a specified seat? (y/n) ";
    char answer;
    if (!read_yes_no(answer)) return;
    int seat = first_available + 1;
    if (answer == 'y') {
        cout << "Enter the seat number: ";
        while (true) {
            if (!read_integer(seat, 1, 15)) return;
            if (!theater.reserved[seat - 1]) break;
            cout << "The seat has been reserved, please enter your selection again: ";
        }
    }
    theater.reserved[seat - 1] = true;
    cout << "The seat number " << seat << " is reserved for you...\n";
}
void cancel_seat(Theater& theater) {
    cout << "***Cancel an existing reservation***\nPlease enter the seat number which you want to cancel: ";
    int seat;
    if (!read_integer(seat, 1, 15)) return;
    if (theater.reserved[seat - 1]) {
        theater.reserved[seat - 1] = false;
        cout << "The seat number " << seat << " is available now...\n";
    } else cout << "The seat is not reserved\n";
}
void show_available(const Theater& theater) {
    cout << "***Show the all available seats***\n";
    for (int i = 0; i < 15; ++i) if (!theater.reserved[i]) cout << "seat " << i + 1 << '\n';
}
void show_seats(const Theater& theater) {
    cout << "***Show the status of all seats***\nSeat number       Status\n";
    for (int i = 0; i < 15; ++i)
        cout << "Seat " << left << setw(13) << i + 1 << (theater.reserved[i] ? "reserved" : "available") << '\n';
}
void show_member(const Theater& theater) {
    cout << "***NCU Theater Membership***\n";
    if (theater.members.empty()) {
        cout << "No Member\n";
        return;
    }
    size_t name_width = 12;
    for (size_t i = 0; i < theater.members.size(); ++i)
        name_width = max(name_width, theater.members[i].username.size() + 2);
    cout << left << setw(5) << "No." << setw(static_cast<int>(name_width))
         << "Username" << "Phone\n";
    for (size_t i = 0; i < theater.members.size(); ++i)
        cout << left << setw(5) << (to_string(i + 1) + ".")
             << setw(static_cast<int>(name_width)) << theater.members[i].username
             << theater.members[i].phone << '\n';
}
void load_member(Theater& theater) {
    cout << "***Load member information***\nPlease enter the member file name: ";
    string filename;
    if (!(cin >> filename)) return;
    ifstream infile(filename.c_str(), ios::in);
    if (!infile) { cout << "File could not be opened.\n"; return; }
    vector<MemberData> pending;
    string line;
    bool first_row = true;
    while (getline(infile, line)) {
        istringstream row(line);
        if (!(row >> ws) || row.eof()) continue;
        MemberData member;
        string extra;
        if (!(row >> member.username >> member.password >> member.phone) || (row >> extra)) {
            cout << "Invalid member data.\n";
            return;
        }
        if (first_row && member.username == "Name" && member.password == "Password"
            && member.phone == "Phone") {
            first_row = false;
            continue;
        }
        first_row = false;
        bool duplicate = false;
        for (size_t i = 0; i < theater.members.size(); ++i)
            duplicate = duplicate || theater.members[i].username == member.username;
        for (size_t i = 0; i < pending.size(); ++i)
            duplicate = duplicate || pending[i].username == member.username;
        if (member.username.size() > 50 || member.password.size() > 50 || duplicate
            || theater.members.size() + pending.size() >= 15) {
            cout << "Invalid member data.\n";
            return;
        }
        pending.push_back(member);
    }
    if (infile.bad()) { cout << "Invalid member data.\n"; return; }
    theater.members.insert(theater.members.end(), pending.begin(), pending.end());
    cout << "The file " << filename << " has been loaded...\n";
}
void change_member(Theater& theater) {
    cout << "***Change member data***\nPlease type 1 to change password\n"
         << "Please type 2 to change phone number\nEnter your selection Here: ";
    int selection;
    if (!read_integer(selection, 1, 2)) return;
    string username, password, replacement;
    cout << "Enter Username: ";
    if (!read_text(username)) return;
    cout << "Enter Password: ";
    if (!read_text(password)) return;
    const int member = authenticate(theater, username, password);
    if (member == -1) { cout << "The username and the password don't match.\n"; return; }
    cout << (selection == 1 ? "Enter the new password: " : "Enter the new phone number: ");
    if (!read_text(replacement, selection == 1)) return;
    if (selection == 1) theater.members[member].password = replacement;
    else theater.members[member].phone = replacement;
}
void find_member(const Theater& theater) {
    cout << "***Find member data***\nPlease enter the search keyword: ";
    string keyword;
    if (!read_text(keyword, false)) return;
    cout << "\nThe searching keyword is \"" << keyword << "\"...\n"
         << "The searching results are as follows:\n";
    bool found = false;
    for (size_t i = 0; i < theater.members.size(); ++i) {
        const MemberData& member = theater.members[i];
        if (member.username.find(keyword) != string::npos) {
            if (!found) cout << "*** Customer Information ***\n"
                             << left << setw(16) << "Name" << ' ' << setw(16) << "Password" << " Phone\n";
            cout << left << setw(16) << member.username << ' ' << setw(16) << member.password << ' ' << member.phone << '\n';
            found = true;
        }
    }
    if (!found) cout << "We cannot find the keyword\n";
}
int main() {
    Theater theater;
    while (true) {
        cout << "*** Welcome to NCU theater reservation system ***\n";
        if (theater.logged_in >= 0)
            cout << "***Welcome back " << theater.members[theater.logged_in].username << "***\n";
        cout << "Please type 1 to make a new reservation\n"
             << "Please type 2 to cancel an existing reservation\n"
             << "Please type 3 to show the all available seats\n"
             << "Please type 4 to show the status of all current seats\n";
        cout << (theater.logged_in >= 0 ? "Please type 5 to log-out\n" : "Please type 5 to member center\n");
        cout << "Please type 6 to show member\n";
        cout << "Please type 7 to load member information\n";
        cout << "Please type 8 to change member data\n";
        cout << "Please type 9 to find member data\n";
        cout << "Please type 10 to exit the system\n";

        cout << "Enter your selection Here: ";
        int selection;
        if (!read_integer(selection, 1, 10)) return 0;
        cout << '\n';
        if (selection == 10) {
            cout << "Thank you for using our system\nHave a nice day~~\n";
            return 0;
        }
        switch (selection) {
            case 1: reserve_seat(theater); break;
            case 2: cancel_seat(theater); break;
            case 3: show_available(theater); break;
            case 4: show_seats(theater); break;
            case 5:
                if (theater.logged_in >= 0) theater.logged_in = -1;
                else Member(theater);
                break;
            case 6: show_member(theater); break;
            case 7: load_member(theater); break;
            case 8: change_member(theater); break;
            case 9: find_member(theater); break;

        }
        if (!cin) return 0;
        cout << '\n';
    }
}
```
<!-- SOLUTION_CODE_END -->
