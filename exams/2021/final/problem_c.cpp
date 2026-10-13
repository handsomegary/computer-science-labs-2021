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
