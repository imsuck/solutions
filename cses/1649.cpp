#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...) 42
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

template<typename T> struct SegTree {
    i32 n;
    vec<T> t;
    SegTree(i32 n) : n(n), t(2*n) {}
    SegTree(vec<T> const &v) : SegTree(v.size()) {
        for (i32 i = 0; i < v.size(); i++) 
            t[i + n] = v[i];
        for (i32 i = n-1; i > 0; i--)
            t[i] = min(t[i<<1], t[i<<1|1]);
    }
    void update(i32 p, i32 val) {
        for (t[p += n] = val; p > 1; p >>= 1)
            t[p>>1] = min(t[p], t[p^1]);
    }
    i32 query(i32 l, i32 r) {
        i32 mn = 1e9 + 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) mn = min(mn, t[l++]);
            if (r&1) mn = min(mn, t[--r]);
        }
        return mn;
    }
};

void solve() {
    i32 n, q;
    cin >> n >> q;
    vec<i32> v(n);
    for (i32 &i : v)
        cin >> i;
    SegTree<i32> st(v);
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}
