#pragma once

struct DSU {
    vector<int> par, sz;
    DSU() : DSU(0) {}
    DSU(int n) : par(n), sz(n, 1) { iota(begin(par), end(par), 0); }

    int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        return merge(x, y, [](auto...) {});
    }
    template<class F> bool merge(int x, int y, F &&f) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        sz[x] += sz[y], par[y] = x;
        f(x, y);
        return true;
    }
};
