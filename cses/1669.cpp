#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"
#include "library/other/y_combinator.hpp"

#define fn auto

fn solve() {
    i32 n, m;
    cin >> n >> m;
    vec<basic_string<i32>> g(n);
    for (i32 i = 0, u, v; i < m; i++) {
        cin >> u >> v, u--, v--;
        g[u] += v, g[v] += u;
    }
    bool f = 0;
    vec<i32> vis(n), dep(n), cycl;
    auto dfs = y_comb([&](auto &self, i32 v, i32 p = -1) -> i32 {
        vis[v] = 1;
        for (i32 u : g[v]) {
            if (u == p) continue;
            if (vis[u]) {
                f = 1;
                cycl.push_back(v);
                return dep[v] - dep[u];
            }
            dep[u] = dep[v] + 1;
            i32 len = self(u, v);
            if (f) {
                if (len > 0) cycl.push_back(v);
                return len - 1;
            }
        }
        return 0;
    });
    for (i32 i = 0; i < n; i++) {
        if (vis[i]) continue;
        dfs(i);
        if (f) {
            cycl.push_back(cycl[0]);
            cout << cycl.size() << "\n";
            for (i32 v : cycl) cout << v + 1 << " ";
            cout << "\n";
            return;
        }
    }
    cout << "IMPOSSIBLE\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
