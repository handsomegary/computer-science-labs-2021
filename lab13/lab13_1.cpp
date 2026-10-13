// Based on the original lab; retain leading zeros and process 1-10 invoices.
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main() {
    string sentence, line, lottery, invoice;
    if (!getline(cin, sentence) || !getline(cin, line)) return 0;
    const size_t begin = sentence.find_first_of("0123456789");
    if (begin == string::npos || sentence.size() < begin + 8) return 0;
    lottery = sentence.substr(begin, 8);
    istringstream invoices(line);
    int total = 0, count = 0;
    cout << '\n';
    while (invoices >> invoice && count++ < 10) {
        if (invoice.size() != 8 || invoice.find_first_not_of("0123456789") != string::npos) continue;
        int matched = 0;
        while (matched < 8 && invoice[7 - matched] == lottery[7 - matched]) ++matched;
        int prize = 0;
        string description;
        switch (matched) {
            case 3: prize = 200; description = "2 hundred"; break;
            case 4: prize = 1000; description = "1 thousand"; break;
            case 5: prize = 4000; description = "4 thousand"; break;
            case 6: prize = 10000; description = "10 thousand"; break;
            case 7: prize = 40000; description = "40 thousand"; break;
            case 8: prize = 200000; description = "200 thousand"; break;
        }
        if (prize) { cout << invoice << " won " << description << " dollars!\n"; total += prize; }
    }
    if (total) cout << "You totally won " << total << " dollars !!!\n";
    else cout << "Won nothing. But, less is more.\n";
}
