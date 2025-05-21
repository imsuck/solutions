#include <bits/stdc++.h>
using namespace std;

struct DSU {
    using i32 = int32_t;
    vector<i32> par, sz;
    DSU() : DSU(0) {}
    DSU(i32 n) : par(n), sz(n, 1) { iota(begin(par), end(par), 0); }

    i32 find(i32 x) { return x == par[x] ? x : par[x] = find(par[x]); }
    bool same(i32 x, i32 y) { return find(x) == find(y); }
    bool merge(i32 x, i32 y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        sz[x] += sz[y];
        par[y] = x;
        return true;
    }
};
