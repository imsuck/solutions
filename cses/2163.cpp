#include <bits/stdc++.h>
using namespace std;
#include "library/other/types.hpp"

struct fenwick_tree {
    i32 n = 1, m = 1;
    vec<i32> t;
    fenwick_tree(i32 _n) : n(_n), t(n + 1) {
        while (2 * m <= n) m *= 2;
    }
    fenwick_tree(const vec<i32> &v) : fenwick_tree((i32)v.size()) {
        for (i32 i = 1; i <= n; i++) {
            t[i] += v[i - 1];
            i32 j = i + (i & -i);
            if (j <= n) t[j] += t[i];
        }
    }
    void add(i32 p, i32 d) {
        for (p++; p <= n; p += p & -p) t[p] += d;
    }
    i32 prefix_lower_bound(i32 k) const {
        i32 x = 0;
        for (i32 i = m; i; i >>= 1) {
            if (x + i > n || t[x + i] > k) continue;
            x += i;
            k -= t[x];
        }
        return x;
    }
};

void solve() {
    i32 n, k;
    cin >> n >> k;
    fenwick_tree t(vec<i32>(n, 1));
    for (i32 i = 0, sz = n, j; sz; sz--) {
        i = (i + k) % sz;
        cout << (j = t.prefix_lower_bound(i)) + 1 << " \n"[sz == 1];
        t.add(j, -1);
    }
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
