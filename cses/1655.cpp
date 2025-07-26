#include <bits/stdc++.h>
using namespace std;

template<int L> struct BinTrie {
    struct node {
        array<int, 2> c{-1, -1};
    };
    int new_node() { return t.emplace_back(), (int)t.size() - 1; }
    vector<node> t;

    BinTrie() : t(1) {}

    void insert(int x) {
        int p = 0;
        for (int i = L - 1; i >= 0; i--) {
            bool f = x >> i & 1;
            if (t[p].c[f] == -1) t[p].c[f] = new_node();
            p = t[p].c[f];
        }
    }
    int max_xor(int x) const {
        int p = 0, res = 0;
        for (int i = L - 1; i >= 0; i--) {
            bool f = x >> i & 1;
            if (t[p].c[!f] != -1) {
                res |= 1 << i;
                p = t[p].c[!f];
            } else {
                p = t[p].c[f];
            }
        }
        return res;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int s = 0, mx = 0;
    BinTrie<30> tr;
    tr.insert(s);
    for (int i = 0, a; i < n; i++) {
        cin >> a, s ^= a;
        mx = max(mx, tr.max_xor(s));
        tr.insert(s);
    }
    cout << mx << "\n";
}
