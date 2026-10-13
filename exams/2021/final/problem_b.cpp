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
