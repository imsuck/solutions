#include <bits/stdc++.h>
using namespace std;

struct DSU {
    using i32 = int32_t;
    vector<i32> par;
    DSU() : DSU(0) {}
    DSU(i32 n) : par(n) {
        for (i32 &i : par)
            i = -1;
    }

    i32 find_set(i32 v) { return par[v] < 0 ? v : par[v] = find_set(par[v]); }

    bool union_sets(i32 a, i32 b) {
        a = find_set(a), b = find_set(b);
        if (a == b)
            return false;
        if (-par[a] < -par[b])
            swap(a, b);
        par[a] += par[b];
        par[b] = a;
        return true;
    }
};
