#include <bits/stdc++.h>
using namespace std;
#include "library/math/modint.hpp"
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto
using mint = modint107;

fn solve() {
    i32 n;
    cin >> n;
    if (n * (n + 1) % 4 != 0) {
        cout << "0\n";
        return;
    }
    i32 tot = n * (n + 1) / 2;
    vec<mint> dp(tot + 1);
    dp[0] = 1;
    for (i32 i = 1; i <= n; i++)
        for (i32 j = tot; j >= i; j--) dp[j] += dp[j - i];
    cout << dp[tot / 2] / 2 << "\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
