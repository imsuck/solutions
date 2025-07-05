#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
#endif

#define fn auto
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using str = string;
template<class T> using vec = vector<T>;

const i32 mod = i32(1e9) + 7;
i32 add(i32 a, i32 b) { return (a -= mod - b) < 0 ? a + mod : a; }
i32 mul(i32 a, i32 b) { return i32(i64(a) * b % mod); }

fn solve() {
    i32 n, m;
    cin >> n >> m;
    vec<i32> a(n);
    vec<vec<i32>> dp(n, vec<i32>(m + 1, 0));
    for (i32 &i : a) cin >> i;
    if (a[0] == 0) {
        dp[0] = vec<i32>(m + 1, 1);
        dp[0][0] = 0;
    } else {
        dp[0][a[0]] = 1;
    }
    for (i32 i = 1; i < n; i++) {
        if (a[i] == 0) {
            for (i32 j = 1; j <= m; j++) {
                for (i32 k = max(j - 1, 1); k <= min(j + 1, m); k++) {
                    dp[i][j] = add(dp[i][j], dp[i - 1][k]);
                }
            }
        } else {
            for (i32 j = max(a[i] - 1, 1); j <= min(a[i] + 1, m); j++) {
                dp[i][a[i]] = add(dp[i][a[i]], dp[i - 1][j]);
            }
        }
    }
    i32 ans = 0;
    for (i32 i : dp.back()) ans = add(ans, i);
    cout << ans << "\n";
}

fn main() -> i32 {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 t = 1;
    // cin >> t;
    while (t--) solve();
}
