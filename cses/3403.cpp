#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto
auto chmax = [](auto &a, auto &&b) { return a < b ? a = b, 1 : 0; };

fn solve() {
    i32 n, m;
    cin >> n >> m;
    vec<i32> a(n + 1), b(m + 1);
    for (i32 i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (i32 i = 1; i <= m; i++) {
        cin >> b[i];
    }

    using P = pair<i32, i32>;
    vec<vec<i32>> dp(n + 1, vec<i32>(m + 1));
    vec<vec<P>> from(n + 1, vec<P>(m + 1, P(-1, -1)));
    i32 x = -1, y = -1, mx = 0;
    for (i32 i = 1; i <= n; i++) {
        for (i32 j = 1; j <= m; j++) {
            if (a[i] == b[j] && chmax(dp[i][j], dp[i - 1][j - 1] + 1)) {
                from[i][j] = P(i, j);
            }
            if (chmax(dp[i][j], dp[i - 1][j])) {
                from[i][j] = from[i - 1][j];
            }
            if (chmax(dp[i][j], dp[i][j - 1])) {
                from[i][j] = from[i][j - 1];
            }
            if (chmax(mx, dp[i][j])) {
                tie(x, y) = tie(i, j);
            }
        }
    }
    vec<i32> res;
    for (; x != -1; tie(x, y) = from[x - 1][y - 1]) {
        res.push_back(b[y]);
    }
    reverse(begin(res), end(res));
    cout << res.size() << "\n";
    for (i32 i = 0; i < res.size(); i++) {
        cout << res[i] << " \n"[i == res.size() - 1];
    }
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
