#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
using i64 = int64_t;
template<typename T> using vec = vector<T>;

struct SegTree {
    i32 n;
    vec<i64> t;
    SegTree(i32 n) : n(n), t(2*n) {};
    SegTree(vec<i64> const &v) : SegTree(v.size()) {
        for (i32 i = 0; i < v.size(); i++)
            t[i + n] = v[i];
        for (i32 i = n - 1; i > 0; i--)
            t[i] = t[i<<1] + t[i<<1|1];
    };
    void update(i32 v, i32 val) {
        for (t[v += n] = val; v > 1; v >>= 1)
            t[v>>1] = t[v] + t[v^1];
    }
    i64 query(i32 l, i32 r) {
        i64 res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += t[l++];
            if (r&1) res += t[--r];
        }
        return res;
    }
};

i32 main() {
    cin.tie(0)->sync_with_stdio(0);
    i32 n, q;
    cin >> n >> q;
    vec<i64> v(n);
    for (i64 &i : v) cin >> i;
    SegTree st(v);
    while (q--) {
        i32 ty, a, b;
        cin >> ty >> a >> b;
        a--;
        if (ty == 1)
            st.update(a, b);
        else
            cout << st.query(a, b) << "\n";
    }
}
