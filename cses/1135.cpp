#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;

    vector<vector<int>> g(n);
    for (int i = 0, u, v; i < n - 1; i++)
        cin >> u >> v, g[--u].push_back(--v), g[v].push_back(u);

    vector<int> sz(n, 1), par(n), in(n), hs(n), dp(n);
    auto dfs_sz = [&](auto self, int v = 0, int p = -1) -> void {
        par[v] = p;
        if (g[v].size() && g[v][0] == p) swap(g[v][0], g[v].back());
        for (int &c : g[v]) {
            if (c == p) continue;
            dp[c] = dp[v] + 1, self(self, c, v), sz[v] += sz[c];
            if (sz[g[v][0]] < sz[c]) swap(g[v][0], c);
        }
    };
    dfs_sz(dfs_sz);

    int t = 0;
    auto decomp = [&](auto self, int v = 0, int p = -1) -> void {
        in[v] = t++;
        for (int c : g[v]) {
            if (c == p) continue;
            hs[c] = (c == g[v][0] ? hs[v] : c);
            self(self, c, v);
        }
    };
    decomp(decomp);

    auto lca = [&](int u, int v) {
        for (;; v = par[hs[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (hs[u] == hs[v]) return u;
        }
    };
    auto dist = [&](int u, int v) {
        int p = lca(u, v);
        return dp[u] + dp[v] - 2 * dp[p];
    };

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << dist(a - 1, b - 1) << "\n";
    }
}
