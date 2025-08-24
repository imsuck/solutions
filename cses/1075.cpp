#include <bits/stdc++.h>
using namespace std;
#include "library/math/modint.hpp"
#include "library/other/types.hpp"

#define fn auto
const i32 N = 1001;
using mint = modint107;
mint dp[N][N][3];
// dp[i][j][k], i = cur num, j = |CCs|, k = CCs adjacent to cur num
// k = 0: join 2 CCs
// k = 1: add to one end of an existing CC
// k = 2: its own CC
// Note: dp counts unordered components unlike in:
// https://codeforces.com/blog/entry/92602

fn solve() {
    i32 n, m, k;
    cin >> n >> m >> k;

    dp[1][1][2] = 1;
    for (i32 i = 2; i <= n; i++) {
        for (i32 j = 1; j <= n; j++) {
            dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = 0;

            dp[i][j][0] += (j + 1) * j * dp[i - 1][j + 1][0];
            dp[i][j][0] += j * j * dp[i - 1][j + 1][1];
            dp[i][j][0] += j * (j - 1) * dp[i - 1][j + 1][2];

            dp[i][j][1] += 2 * j * dp[i - 1][j][0];
            dp[i][j][1] += (2 * j - 1) * dp[i - 1][j][1];
            dp[i][j][1] += (2 * j - 2) * dp[i - 1][j][2];

            dp[i][j][2] += dp[i - 1][j - 1][0];
            dp[i][j][2] += dp[i - 1][j - 1][1];
            dp[i][j][2] += dp[i - 1][j - 1][2];
        }
    }
    cout << accumulate(dp[n][1], dp[n][1] + 3, mint(0)) << "\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
