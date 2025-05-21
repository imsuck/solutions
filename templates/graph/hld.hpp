#include <cassert>
#include <vector>
using namespace std;

struct HLD {
    int n;
    vector<int> sz, par, in, out, hs;

    template<class G>
    HLD(G &g, int root = 0) :
        n(int(g.size())), sz(n, 1), par(n), in(n), out(n), hs(n) {
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
