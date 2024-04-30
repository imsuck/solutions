#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define pb push_back
#define pp pop_back
#define eb emplace_back

struct SegTree {
    i32 n;
    vec<i32> t;

    SegTree(i32 n) : n(n), t(4 * n){};

    void _update(i32 v, i32 tl, i32 tr, i32 i, i32 val) {
        if (tl == tr)
            return void(t[v] += val);
        i32 tm = (tl + tr) / 2;
        if (i <= tm)
            _update(v * 2, tl, tm, i, val);
        else
            _update(v * 2 + 1, tm + 1, tr, i, val);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }

    i32 _query(i32 v, i32 tl, i32 tr, i32 l, i32 r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return t[v];
        i32 tm = (tl + tr) / 2;
        return _query(v * 2, tl, tm, l, min(r, tm)) +
               _query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    }

    void update(i32 i, i32 v) { _update(1, 0, n - 1, i, v); }
    i32 query(i32 l, i32 r) { return _query(1, 0, n - 1, l, r); }
};

void solve() {
    i32 n;
    cin >> n;
    vec<tuple<i32, i32, i32>> v(n);
    map<i32, i32> comp;
    for (i32 i = 0; i < n; i++) {
        i32 l, r;
        cin >> l >> r;
        v[i] = {l, r, i};
        comp[l], comp[r];
    }
    i32 cnt = 0;
    for (auto &p : comp) {
        p.second = cnt++;
    }
    for (i32 i = 0; i < n; i++) {
        i32 &l = get<0>(v[i]), &r = get<1>(v[i]);
        l = comp[l], r = comp[r];
    }
    sort(all(v), [](tuple<i32, i32, i32> &a, tuple<i32, i32, i32> &b) {
        i32 la, ra, lb, rb;
        tie(la, ra, ignore) = a, tie(lb, rb, ignore) = b;
        return (la == lb && ra > rb) || la < lb;
    });
    SegTree st(cnt);
    vec<i32> ans(n);
    for (i32 i = n - 1; i >= 0; i--) {
        i32 l, r, idx;
        tie(l, r, idx) = v[i];
        ans[idx] = st.query(0, r);
        st.update(r, 1);
    }
    for (i32 i = 0; i < n; i++)
        cout << ans[i] << " \n"[i == n - 1];
    st = SegTree(cnt);
    for (i32 i = 0; i < n; i++) {
        i32 l, r, idx;
        tie(l, r, idx) = v[i];
        ans[idx] = st.query(r, cnt - 1);
        st.update(r, 1);
    }
    for (i32 i = 0; i < n; i++)
        cout << ans[i] << " \n"[i == n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}
