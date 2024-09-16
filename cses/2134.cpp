#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int &i : a) cin >> i;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[--u].push_back(--v);
        g[v].push_back(u);
    }

    vector<int> sz(n), par(n), in(n), nxt(n);
    auto dfs_sz = [&](auto &self, int v = 0, int p = -1) -> void {
        sz[v] = 1;
        par[v] = p;
        if (!g[v].empty() && g[v][0] == p) swap(g[v][0], g[v].back());
        for (int &c : g[v]) {
            if (c == p) continue;
            self(self, c, v);
            sz[v] += sz[c];
            if (sz[g[v][0]] < sz[c]) swap(g[v][0], c);
        }
    };
    dfs_sz(dfs_sz);
    auto dfs_hld = [&, t = 0](auto &self, int v = 0, int p = -1) mutable -> void {
        in[v] = t++;
        for (int c : g[v]) {
            if (c == p) continue;
            nxt[c] = (c == g[v][0] ? nxt[v] : c);
            self(self, c, v);
        }
    };
    dfs_hld(dfs_hld);
    auto lca = [&](int u, int v) {
        for (;; v = par[nxt[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (nxt[u] == nxt[v]) return u;
        }
    };
    auto get_path = [&](int v, int p, bool es = 0) {
        vector<pair<int, int>> res;
        for (; nxt[v] != nxt[p]; v = par[nxt[v]])
            res.emplace_back(in[nxt[v]], in[v] + 1);
        res.emplace_back(in[p] + es, in[v] + 1);
        return res;
    };

    vector<int> tree(n * 2);
    auto update = [&](int p) { tree[p] = max(tree[p << 1], tree[p << 1 | 1]); };
    for (int i = 0; i < n; i++) tree[in[i] + n] = a[i];
    for (int i = n - 1; i; i--) update(i);

    auto set = [&](int p, int x) {
        for (tree[p += n] = x; p >>= 1;) update(p);
    };
    auto prod = [&](int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, tree[l++]);
            if (r & 1) res = max(tree[--r], res);
        }
        return res;
    };

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, x;
            cin >> v >> x;
            v--;
            set(in[v], x);
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            int p = lca(u, v);
            int ans = 0;
            for (auto &[l, r] : get_path(u, p)) ans = max(ans, prod(l, r));
            for (auto &[l, r] : get_path(v, p, 1)) ans = max(ans, prod(l, r));
            cout << ans << " ";
        }
    }
    cout << "\n";
}
