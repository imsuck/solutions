#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto

fn solve() {
    i32 n;
    cin >> n;
    vec<i32> a(n);
    vec<vec<i64>> dp(n + 1, vec<i64>(n + 1));
    i64 sm = 0;
    for (i32 i = 0; i < n; i++) {
        cin >> a[i], sm += a[i];
        dp[i][i + 1] = a[i];
    }

    for (i32 w = 2; w <= n; w++) {
        for (i32 l = 0, r = w; r <= n; l++, r++) {
            dp[l][r] = max(a[l] - dp[l + 1][r], a[r - 1] - dp[l][r - 1]);
        }
    }

    cout << (sm + dp[0][n]) / 2 << "\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
