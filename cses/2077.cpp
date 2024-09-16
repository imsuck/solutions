#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio();
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int u, v;
        cin >> u >> v, g[--u].push_back(--v), g[v].push_back(u);
    }

    int t = 0;
    vector<int> in(n), low(n);
    vector<char> vis(n), ar(n);
    auto dfs = [&](auto self, int v, int p = -1) -> void {
        in[v] = low[v] = t++, vis[v] = true;
        int children = 0;
        for (int u : g[v]) {
            if (u == p) continue;
            if (vis[u]) {
                low[v] = min(low[v], in[u]);
                continue;
            }
            self(self, u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] >= in[v] && p != -1) ar[v] = true;
            children++;
        }
        if (p == -1 && children > 1) ar[v] = true;
    };
    for (int i = 0; i < n; i++) if (!vis[i]) dfs(dfs, i);
    cout << accumulate(begin(ar), end(ar), 0) << "\n";
    for (int i = 0; i < n; i++) if (ar[i]) cout << i + 1 << " ";
    cout << "\n";
}
