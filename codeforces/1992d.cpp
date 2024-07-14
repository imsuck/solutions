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
#define all(a) begin(a), end(a)
#define rall(a) rbegin(a), rend(a)
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n, m, k;
    cin >> n >> m >> k;
    str s;
    cin >> s;
    s = 'L' + s + 'L';
    i32 idx = 0;
    vec<i32> comp(n + 1);
    for (int i = 1; i < n + 1; i++) {
        if (s[i - 1] != 'W' && s[i] == 'W')
            idx = i;
        s[i] == 'W' ? comp[i] = idx : 0;
    }
    vec<i32> dp(n + 2, -1e9);
    dp[0] = k;
    for (i32 i = 1; i < n + 2; i++) {
        if (s[i] == 'C') {
            continue;
        }
        for (int j = max(i - m, 0); j < i; j++) {
            if (s[j] == 'L') {
                dp[i] = max(dp[i], dp[j] - (s[i] == 'W'));
            }
        }
        if (s[i] == 'L' && s[i - 1] == 'W') {
            dp[i] = max(dp[i], dp[i - 1]);
        }
        if (s[i] != 'W') {
            continue;
        }
        for (int j = comp[i]; j < i; j++) {
            dp[i] = max(dp[i], dp[j] - i + j);
        }
    }
    cout << (dp.back() >= 0 ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}
