#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using u64 = uint64_t;

template<class I> const I inf = numeric_limits<I>::max();

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int64_t> d(n, -inf<i64>);
    d[0] = 0;
    vector<basic_string<int>> g(n);
    vector<array<int, 3>> edges(m);
    for (int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w, u--, v--;
        g[u] += v, edges[i] = {u, v, w};
    }
    vector<bool> bad(n), vis(n);
    for (int i = 1; i <= n; i++) {
        for (auto [u, v, w] : edges) {
            if (d[u] == -inf<i64>) continue;
            if (d[v] < d[u] + w) {
                d[v] = min(inf<i64> / 3, d[u] + w);
                if (i == n) bad[v] = true;
            }
        }
    }
    auto dfs = [&](auto &f, int v) -> void {
        for (int u : g[v])
            if (!vis[u]) vis[u] = true, f(f, u);
    };
    for (int i = 0; i < n; i++)
        if (bad[i] && !vis[i]) dfs(dfs, i);
    cout << (vis.back() ? -1 : d.back()) << "\n";
}
