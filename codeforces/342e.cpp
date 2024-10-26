#include <bits/stdc++.h>
using namespace std;

struct HLD {
    int n;
    vector<int> sz, par, in, out, hs, dep;

    template<class G> HLD(G &g, int root = 0)
        : n(int(g.size())), sz(n, 1), par(n), in(n), out(n), hs(n), dep(n) {
        dfs_sz(g, root);
        dfs_hld(g, root);
        assert(time == n);
    }

    int lca(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);
        for (;; v = par[hs[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (hs[u] == hs[v]) return u;
        }
    }
    int dist(int u, int v) const {
        assert(0 <= u && u < n && 0 <= v && v < n);
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    auto path(int v, int p, bool es = 0) const {
        assert(in[p] <= in[v] && out[v] <= out[p]);
        vector<pair<int, int>> res;
        for (; hs[v] != hs[p]; v = par[hs[v]])
            res.emplace_back(in[hs[v]], in[v] + 1);
        res.emplace_back(in[p] + es, in[v] + 1);
        return res;
    }
    pair<int, int> subtree(int v) const {
        assert(0 <= v && v < n);
        return {in[v], out[v]};
    }

  private:
    int time = 0;
    template<class G> void dfs_sz(G &g, int v, int p = -1) {
        par[v] = p;
        if (g[v].size() && g[v][0] == p) swap(g[v][0], g[v].back());
        for (int &c : g[v]) {
            if (c == p) continue;
            dep[c] = dep[v] + 1;
            dfs_sz(g, c, v);
            sz[v] += sz[c];
            if (sz[g[v][0]] < sz[c]) swap(g[v][0], c);
        }
    }
    template<class G> void dfs_hld(G &g, int v, int p = -1) {
        in[v] = time++;
        for (int c : g[v]) {
            if (c == p) continue;
            hs[c] = (c == g[v][0] ? hs[v] : c);
            dfs_hld(g, c, v);
        }
        out[v] = time;
    }
};

template<class G>
tuple<vector<int>, vector<int>, vector<int>> centroid_decomp(const G &g) {
    const int N = int(g.size());
    vector<int> sz(N), lvl(N, -1), sz_comp(N), par(N);

    auto dfs_sz = [&](auto &dfs, int v, int p) -> int {
        sz[v] = 1;
        for (int c : g[v])
            if (c != p && lvl[c] == -1) sz[v] += dfs(dfs, c, v);
        return sz[v];
    };
    auto dfs_cent = [&](auto &dfs, int v, int p, int n) -> int {
        for (int c : g[v])
            if (c != p && lvl[c] == -1 && sz[c] > n / 2)
                return dfs(dfs, c, v, n);
        return v;
    };
    auto decomp = [&](auto &dfs, int v, int k, int p) -> void {
        int n = dfs_sz(dfs_sz, v, -1);
        int s = dfs_cent(dfs_cent, v, -1, n);
        lvl[s] = k, sz_comp[s] = n, par[s] = p;
        for (int c : g[s])
            if (lvl[c] == -1) dfs(dfs, c, k + 1, s);
    };

    decomp(decomp, 0, 0, -1);
    return {lvl, sz_comp, par};
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<basic_string<int>> g(n);
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[--u].push_back(--v), g[v].push_back(u);
    }
    HLD hld(g);
    auto [lvl, sz_comp, par] = centroid_decomp(g);

    vector<int> mnd(n, 1e9);
    auto paint = [&](int v) {
        mnd[v] = 0;
        for (int u = v; u != -1; u = par[u])
            mnd[u] = min(mnd[u], hld.dist(u, v));
    };
    auto query = [&](int v) {
        int mn = mnd[v];
        for (int u = v; u != -1; u = par[u])
            mn = min(mn, hld.dist(u, v) + mnd[u]);
        cout << mn << "\n";
    };

    paint(0);
    while (q--) {
        int t, v;
        cin >> t >> v, v--;
        if (t == 1) paint(v);
        else query(v);
    }
}
