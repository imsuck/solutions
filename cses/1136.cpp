#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n);
    for (int i = 0, u, v; i < n - 1; i++)
       cin >> u >> v, g[--u].push_back(--v), g[v].push_back(u);

    vector<int> sz(n, 1), par(n), in(n), hs(n);
    auto dfs_sz = [&](auto self, int v, int p) -> void {
        par[v] = p;
        if (g[v].size() && g[v][0] == p) swap(g[v][0], g[v].back());
        for (int &c : g[v]) {
            if (c == p) continue;
            self(self, c, v);
            sz[v] += sz[c];
            if (sz[g[v][0]] < sz[c]) swap(g[v][0], c);
        }
    };
    dfs_sz(dfs_sz, 0, -1);
    auto decomp = [&, time = 0](auto &self, int v, int p) mutable -> void {
        in[v] = time++;
        for (int c : g[v]) {
            if (c == p) continue;
            hs[c] = (c == g[v][0] ? hs[v] : c);
            self(self, c, v);
        }
    };
    decomp(decomp, 0, -1);
    auto lca = [&](int u, int v) {
        for (;; v = par[hs[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (hs[u] == hs[v]) return u;
        }
    };
    auto path = [&](int v, int p, bool es = 0) {
        vector<pair<int, int>> res;
        for (; hs[v] != hs[p]; v = par[hs[v]])
            res.emplace_back(in[hs[v]], in[v] + 1);
        res.emplace_back(in[p] + es, in[v] + 1);
        return res;
    };

    vector<int> st(n * 2);
    auto inc = [&](int l, int r) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) st[l++]++;
            if (r & 1) st[--r]++;
        }
    };

    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        int anc = lca(u, v);
        for (auto [l, r] : path(u, anc)) inc(l, r);
        for (auto [l, r] : path(v, anc, 1)) inc(l, r);
    }

    for (int i = 1; i < n; i++) st[i * 2] += st[i], st[i * 2 + 1] += st[i];
    for (int i = 0; i < n; i++) cout << st[in[i] + n] << " \n"[i == n - 1];
}
