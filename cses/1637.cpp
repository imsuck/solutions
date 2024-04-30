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
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n;    
    cin >> n;
    vec<i32> dp(n + 1, 1e9);
    dp[0] = 0;
    for (i32 i = 1; i <= n; i++) {
        for (i32 j = 1; j <= i; j *= 10) {
            dp[i] = min(dp[i], dp[i - i / j % 10] + 1);
        }
    }
    cout << dp.back() << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}
