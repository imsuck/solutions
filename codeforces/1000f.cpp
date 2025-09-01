#include <bits/stdc++.h>
using namespace std;
#include "library/ds/segtree.hpp"
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

struct M {
    using T = pair<i32, i32>;
    static T id() { return {1e9, 0}; }
    static T op(T l, T r) { return min(l, r); }
};

void solve() {
    const i32 N = (i32)5e5 + 1;

    i32 n, q;
    cin >> n;
    vec<i32> a(n);
    for (i32 &i : a) cin >> i;
    cin >> q;
    vec<vec<array<i32, 2>>> qs(n + 1);
    for (i32 i = 0, l, r; i < q; i++) {
        cin >> l >> r, l--;
        qs[r].push_back({l, i});
    }

    SegTree<M> st(n);

    vec<i32> last(N, -1), ans(q);
    for (i32 r = 0; r <= n; r++) {
        for (auto [l, i] : qs[r]) {
            auto [id, x] = st(l, r);
            ans[i] = id < l ? x : 0;
        }
        if (r < n) {
            i32 x = a[r];
            if (last[x] != -1) st[last[x]] = {n, 0};
            st[r] = {last[x], x};
            last[x] = r;
        }
    }

    for (i32 i : ans) cout << i << "\n";
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
