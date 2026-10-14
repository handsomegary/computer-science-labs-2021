#include <iostream>
#include <string>
using namespace std;

void swap(char *x, char *y)
{
    char tmp = *x;
    *x = *y;
    *y = tmp;
}

void reverse(char *first, char *last)
{
    --last;
    while (first < last)
    {
        swap(first, last);
        first++;
        last--;
    }
}

int main()
{
    string str;
    cout << "Please enter a string:" << endl;
    getline(cin, str);
    int tail = str.length();
    reverse(&str[0], &str[tail]);
    cout << endl << "After reversed, the string is:" << endl << str;
    return 0;
}

/*#include <iostream>
#include <string>
using namespace std;

class reverse_str
{
public:
    void set_string(string);
    void print_string();
    void reverse_string();

private:
    string str0;
};*/
