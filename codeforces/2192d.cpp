#include <bits/stdc++.h>
using namespace std;

#include "other/types.hpp"
#include "other/y_combinator.hpp"

template<class T1, class T2> bool chmax(T1 &a, const T2 &b) {
    return a < b ? a = b, 1 : 0;
}

void solve() {
    i32 n;
    cin >> n;
    vector<i32> a(n);
    for (i32 &i : a) cin >> i;
    vector<vector<i32>> g(n);
    for (i32 i = 0; i < n - 1; i++) {
        i32 u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    struct DP {
        i32 h = 0;
        i64 sum = 0, contrib = 0, ans = 0;
    };
    vector<DP> dp(n);

    auto rec = y_comb([&](auto &&f, i32 v, i32 p) -> DP {
        vector<DP> d;
        DP res;
        i64 inc = 0;
        for (i32 c : g[v]) {
            if (c == p) continue;
            d.push_back(f(c, v));
            // apply edge
            chmax(res.h, dp[c].h + 1);
            res.sum += dp[c].sum;
            res.contrib += dp[c].sum + dp[c].contrib;
            chmax(inc, dp[c].ans - dp[c].contrib);
        }
        res.ans = res.contrib + inc;
        i32 N = (i32)d.size();
        vector<i32> pref(N + 1), suf(N + 1);
        for (i32 i = 0; i < N; i++) pref[i + 1] = max(pref[i], d[i].h + 1);
        for (i32 i = N; i--;) suf[i] = max(d[i].h + 1, suf[i + 1]);

        for (i32 i = 0; i < N; i++) {
            i64 cur = res.contrib;
            cur += max(pref[i], suf[i + 1]) * d[i].sum;
            chmax(res.ans, cur);
        }
        // apply vertex
        res.sum += a[v];
        return dp[v] = res;
    });
    rec(0, -1);

    for (i32 i = 0; i < n; i++) {
        cout << dp[i].ans << " \n"[i == n - 1];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    i32 tt;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
