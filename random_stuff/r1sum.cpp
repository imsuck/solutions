//! Find maximum sum non-empty subarray where you can remove at most 1 element.
#include <bits/stdc++.h>
using namespace std;
#include "../library/ds/segtree.hpp"
#include "../library/other/types.hpp"

const i64 inf = 1.1e16;
auto _clamp = [](i64 x) { return max(-inf, min(inf, x)); };

struct Monoid {
    struct T {
        i64 sm0 = 0, l0 = -inf, r0 = -inf, mx0 = -inf, sm1 = -inf, l1 = -inf,
            r1 = -inf, mx1 = -inf;
    };
    static T id() { return {}; }
    // clang-format off
    static T op(T l, T r) {
        return {
            .sm0 = l.sm0 + r.sm0,
            .l0  = max(l.l0, _clamp(l.sm0 + r.l0)),
            .r0  = max(_clamp(l.r0 + r.sm0), r.r0),
            .mx0 = max({l.mx0, r.mx0, _clamp(l.r0 + r.l0)}),
            .sm1 = _clamp(max({l.sm0 + r.sm0, l.sm1 + r.sm0, l.sm0 + r.sm1})),
            .l1  = max({l.l1, l.sm1 + r.l0, l.sm0 + r.l1}),
            .r1  = max({r.r1, l.r1 + r.sm0, l.r0 + r.sm1}),
            .mx1 = max({l.mx1, l.r0 + r.l1, l.r1 + r.l0, r.mx1}),
        };
    }
    // clang-format on
};

void solve() {
    auto mk = [](i32 x) -> Monoid::T { return {x, x, x, x, 0, 0, 0, x}; };
    i32 n, q;
    cin >> n >> q;
    SegTree<Monoid> st(n, [&](i32) {
        i32 x;
        cin >> x;
        return mk(x);
    });
    while (q--) {
        i32 op, x, y;
        cin >> op >> x >> y, x--;
        if (op == 1) {
            st[x] = mk(y);
        } else {
            auto res = st(x, y);
            cout << max(res.mx0, res.mx1) << "\n";
        }
    }
}

i32 main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
}
