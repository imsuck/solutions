#include <bits/stdc++.h>
using namespace std;

// clang-format off
struct DSU {
    using i32 = int32_t;
    vector<i32> par, sz;
    DSU() : DSU(0) {}
    DSU(i32 n) : par(n), sz(n, 1) {
        iota(begin(par), end(par), 0);
    }

    i32 find(i32 v) { return v == par[v] ? v : par[v] = find(par[v]); }
    bool same(i32 a, i32 b) { return find(a) == find(b); }
    bool merge(i32 a, i32 b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b];
        par[b] = a;
        return true;
    }
};
// clang-format on
