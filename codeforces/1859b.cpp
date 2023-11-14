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

const i32 INF = 1e9 + 7;

void solve() {
    i32 n;
    cin >> n;
    i64 mn1 = INF, mn2 = INF, s = 0;
    for (i32 i = 0; i < n; i++) {
        i32 m;
        cin >> m;
        vec<i64> v(m);
        for (i64 &x : v) {
            cin >> x;
        }
        sort(all(v));
        mn1 = min(mn1, v[0]);
        mn2 = min(mn2, v[1]);
        s += v[1];
    }

    cout << s + mn1 - mn2 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
