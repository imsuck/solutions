#include "bits/stdc++.h"
using namespace std;

ostream cnull(nullptr);
#ifndef LOCAL
#define cerr cnull
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i64 n;
    cin >> n;
    i64 a[n], d[n];
    vec<i64> oof;
    bool exists[n + 1];
    fill_n(exists, n + 1, false);
    a[0] = d[0] = 0;
    for (i32 i = 1; i <= n - 1; i++) {
        cin >> a[i];
        d[i] = a[i] - a[i - 1];
        if (1 <= d[i] && d[i] <= n && !exists[d[i]]) {
            exists[d[i]] = true;
        } else {
            oof.eb(d[i]);
        }
    }
    if (oof.size() == 0) {
        cout << "YES\n";
        return;
    }
    if (oof.size() >= 2) {
        cout << "NO\n";
        return;
    }
    vec<i64> rem;
    for (i32 i = 1; i <= n; i++) {
        if (!exists[i]) {
            rem.eb(i);
        }
    }
    if (rem.size() == 2 && rem[0] + rem[1] == oof[0]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
