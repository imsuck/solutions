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

void solve() {
    i32 n;
    i64 k, s = 0;
    cin >> n >> k;
    vec<i64> a(n);
    for (i64 &i : a) {
        cin >> i;
        s += i;
    }
    if (s <= k) {
        cout << n << "\n";
        return;
    }
    i64 l = (k + 1) / 2, r = k / 2;
    i32 cntl = 0, cntr = 0;
    for (i32 i = 0; i < n && l > 0; i++) {
        if (l >= a[i])
            cntl++;
        l -= min(l, a[i]);
    }
    for (i32 i = n - 1; i >= 0 && r > 0; i--) {
        if (r >= a[i])
            cntr++;
        r -= min(r, a[i]);
    }
    cout << cntl + cntr << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}
