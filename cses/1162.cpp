#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"

struct fenwick_tree {
    int n;
    vector<int> t;
    fenwick_tree(int _n) : n(_n), t(n + 1) {}
    void add(int p, int d) {
        for (p++; p <= n; p += p & -p) t[p] += d;
    }
    int sum(int l, int r) const {
        int s = 0;
        for (; l; l &= l - 1) s -= t[l];
        for (; r; r &= r - 1) s += t[r];
        return s;
    }
};

void solve() {
    int64_t inv = 0;
    int n, cycl = 0, idk = 0;
    cin >> n;
    vector<int> p(n), lis;
    fenwick_tree t(n);
    for (int &i : p) {
        cin >> i, i--;
        inv += t.sum(i, n);
        t.add(i, 1);
        int pos = int(lower_bound(begin(lis), end(lis), i) - begin(lis));
        if (lis.size() == pos) lis.push_back(0);
        lis[pos] = i;
    }
    vector<char> vis(n);
    for (int i = n - 1, x = n - 1; i >= 0; i--) {
        if (p[i] == x) x--, idk++;
        if (vis[i]) continue;
        cycl++;
        for (int v = i; !vis[v]; v = p[v]) vis[v] = true;
    }
    cout << inv << " " << n - cycl << " " << n - lis.size() << " " << n - idk
         << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
