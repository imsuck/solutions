#include <bits/stdc++.h>
using namespace std;

/*********** template stuff ***********/
#ifndef LOCAL
#define dbg(...)
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
/*********** template stuff ***********/

void solve() {
    str s;
    cin >> s;
    i32 n = s.len();
    vec<i32> l(n, 0), r(n, 0);
    vec<vec<i32>> dp(1, vec<i32>(2, 0));
    for (i32 i = 0; i < n; i++) {
        if (i == 0 || s[i - 1] == 'B') {
            l[i] = 0;
        } else {
            l[i] = l[i - 1] + 1;
        }
    }
    for (i32 i = n - 1; i >= 0; i--) {
        if (i == n - 1 || s[i + 1] == 'B') {
            r[i] = 0;
        } else {
            r[i] = r[i + 1] + 1;
        }
    }
    for (i32 i = 0; i < n; i++) {
        if (s[i] == 'B') {
            dp.eb(vec<i32>{dp.back()[0] + l[i],
                           max(dp.back()[0], dp.back()[1]) + r[i]});
        }
    }
    cout << max(dp.back()[0], dp.back()[1]) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
