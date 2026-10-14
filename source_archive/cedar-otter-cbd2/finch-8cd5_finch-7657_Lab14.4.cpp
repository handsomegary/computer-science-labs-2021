#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;
class reverse_str {
public:
    void set_string(string);
    void print_string();
    void reverse_string();
private:
    string str0;
};

void reverse_str::set_string(string aa) {
    str0 = aa;
}
void reverse_str::print_string() {
    cout << endl << "After reversed, the string is:" << endl << str0;
}
void reverse_str::reverse_string() {
    string tmp = str0;
    for (int i = 0;i < str0.length();i++) {
        str0[i] = tmp[str0.length() - i - 1];
    }
}

int main() {
    reverse_str asdfgh;
    string aa;
    cout << "Please enter a string:\n";
    getline(cin, aa);
    asdfgh.set_string(aa);
    asdfgh.reverse_string();
    asdfgh.print_string();
}