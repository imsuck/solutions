#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v, g[--u].push_back(--v), g[v].push_back(u);
    }

    vector<pair<int, int>> br;
    int t = 0;
    vector<int> in(n), low(n);
    vector<char> vis(n);
    auto dfs = [&](auto self, int v, int p = -1) -> void {
        in[v] = low[v] = t++, vis[v] = true;
        for (int u : g[v]) {
            if (u == p) continue;
            if (vis[u]) {
                low[v] = min(low[v], in[u]);
                continue;
            }
            self(self, u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] > in[v]) br.emplace_back(u, v);
        }
    };
    for (int i = 0; i < n; i++) if (!vis[i]) dfs(dfs, i);
    cout << br.size() << "\n";
    for (auto [u, v] : br) cout << u + 1 << " " << v + 1 << "\n";
}
