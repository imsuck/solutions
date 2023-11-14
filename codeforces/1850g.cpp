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
    i64 n, ans = 0;
    cin >> n;
    array<i64, 2> a[n];
    map<i64, i64> s, e, se, ne;
    for (i32 i = 0; i < n; i++) {
        i64 x, y;
        cin >> x >> y;
        a[i][0] = x;
        a[i][1] = y;
        s[x]++;
        e[y]++;
        se[x + y]++;
        ne[x - y]++;
    }
    for (i32 i = 0; i < n; i++) {
        i64 x = a[i][0], y = a[i][1];
        ans += s[x] - 1;
        ans += e[y] - 1;
        ans += se[x + y] - 1;
        ans += ne[x - y] - 1;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
