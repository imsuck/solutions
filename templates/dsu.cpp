#include <bits/stdc++.h>
using namespace std;

struct DSU {
    using i32 = int32_t;
    vector<i32> par, sz;
    DSU() : DSU(0) {}
    DSU(i32 n) : par(n), sz(n, 1) {
        iota(begin(par), end(par), 0);
    }

    i32 find_set(i32 v) { return v == par[v] ? v : par[v] = find_set(par[v]); }

    bool union_sets(i32 a, i32 b) {
        a = find_set(a), b = find_set(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        sz[a] += sz[b];
        par[b] = a;
        return true;
    }
};
