#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"
#include "library/other/y_combinator.hpp"

#define fn auto
template<class T> using pqueue = priority_queue<T, vec<T>, greater<>>;
auto chmax = [](auto &a, auto &&b) { return a < b ? a = b, 1 : 0; };

fn solve() {
    i32 n, m;
    cin >> n >> m;
    vec<basic_string<i32>> g(n);
    for (i32 i = 0, u, v; i < m; i++) cin >> u >> v, g[--u] += --v;

    vec<i32> mx(n, -1), from(n, -1);
    i32 ans = y_comb([&](auto &dfs, i32 v) -> i32 {
        if (v == n - 1) return 1;
        if (!mx[v]) return 0;
        if (mx[v] != -1) return mx[v];
        i32 ye = 0;
        for (i32 u : g[v])
            if (chmax(ye, dfs(u))) from[v] = u;
        if (ye == 0) return mx[v] = 0;
        return mx[v] = ye + 1;
    })(0);
    if (!ans) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    cout << ans << "\n";
    for (i32 i = 0; i != -1; i = from[i]) cout << i + 1 << " ";
    cout << "\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
