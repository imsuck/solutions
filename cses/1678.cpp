#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"
#include "library/other/y_combinator.hpp"

#define fn auto
template<class T> using pqueue = priority_queue<T, vec<T>, greater<>>;

fn solve() {
    i32 n, m;
    cin >> n >> m;
    vec<basic_string<i32>> g(n);
    for (i32 i = 0, u, v; i < m; i++) {
        cin >> u >> v, u--, v--;
        g[u] += v;
    }

    vec<i32> vis(n), cycl;
    bool found = 0, stop = 0;
    auto dfs = y_comb([&](auto &self, i32 v) -> void {
        if (vis[v] == 2) return;
        if (vis[v] == 1) {
            cycl.push_back(v);
            found = 1;
            return;
        }
        vis[v] = 1;
        for (i32 u : g[v]) {
            self(u);
            if (found) {
                if (!stop) {
                    cycl.push_back(v);
                    stop |= v == cycl[0];
                }
                break;
            }
        }
        vis[v] = 2;
    });
    for (i32 i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
            if (found) {
                reverse(begin(cycl), end(cycl));
                cout << cycl.size() << "\n";
                for (i32 v : cycl) cout << v + 1 << " ";
                cout << "\n";
                return;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
