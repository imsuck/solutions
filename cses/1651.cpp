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

const i32 N = 2e5 + 1;
i32 n;
i32 a[N];
i64 t[4*N];

void update(i32 v, i32 tl, i32 tr, i32 l, i32 r, i32 val) {
    if (l > r) return;
    if (l == tl && r == tr) return void(t[v] += val);
    i32 tm = (tl + tr) / 2;
    update(v*2, tl, tm, l, min(r, tm), val);
    update(v*2+1, tm+1, tr, max(l, tm+1), r, val);
}

i64 query(i32 v, i32 tl, i32 tr, i32 i) {
    if (tl == tr) return t[v];
    i32 tm = (tl + tr) / 2;
    if (i <= tm) return t[v] + query(v*2, tl, tm, i);
    else return t[v] + query(v*2+1, tm+1, tr, i);
}

void solve() {
    i32 q;
    cin >> n >> q;
    for (i32 i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while (q--) {
        i32 ty;
        cin >> ty;
        if (ty == 1) {
            i32 l, r, val;
            cin >> l >> r >> val;
            update(1, 1, n, l, r, val);
        } else {
            i32 i;
            cin >> i;
            cout << a[i] + query(1, 1, n, i) << "\n";
        }
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
