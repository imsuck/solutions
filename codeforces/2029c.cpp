#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) 42
    #define mark_dbg() if (false)
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f80 = long double;
using str = string;
template<class T> using vec = vector<T>;
template<class T> int len(T &&x) { return int(x.size()); }
#define all(a) begin(a), end(a)
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n;
    cin >> n;
    vec<i32> a(n);
    for (i32 &i : a) {
        cin >> i;
    }

    vec<array<i32, 3>> dp(n);
    dp[0][0] = 1;
    for (i32 i = 1; i < n; i++) {
        auto d = [&](int x) {
            int delta = x < a[i] ? +1 : x > a[i] ? -1 : 0;
            return x + delta;
        };
        dp[i][0] = d(dp[i - 1][0]);
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]);
        dp[i][2] = d(max(dp[i - 1][1], dp[i - 1][2]));
    }
    cout << max(dp.back()[1], dp.back()[2]) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--) solve();
}
