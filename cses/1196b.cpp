#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto
template<class T> using pqueue = priority_queue<T, vec<T>, greater<>>;
 
fn solve() {
    i32 n, m, k;
    cin >> n >> m >> k;
 
    vec<vec<pair<i32, i32>>> g(n);
    for (i32 i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w, u--, v--;
        g[u].emplace_back(v, w);
    }
 
    vec<i32> vis(n);
    vec<i64> d;
    pqueue<pair<i64, i32>> q;
    q.emplace(0, 0);
    while (q.size()) {
        auto [dv, v] = q.top();
        q.pop();
        if (vis[v] >= k) continue;
        vis[v]++;
        if (v == n - 1) {
            d.push_back(dv);
        }
        for (auto [u, w] : g[v]) {
            if (vis[u] == k) continue;
            q.emplace(dv + w, u);
        }
    }
    for (i64 i : d) cout << i << " ";
    cout << "\n";
}
 
fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
