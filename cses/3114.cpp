#include <bits/stdc++.h>
using namespace std;

struct HLD {
    int n;
    vector<int> sz, par, in, out, hs, dep;

    template<class G>
    HLD(G &g, int root = 0)
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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
template<class M> struct SegTree {
    using T = typename M::T;
    SegTree() = default;
    SegTree(int _n) : n(_n), t(n * 2, M::id()) {}
    SegTree(const vector<T> &v) : SegTree(v.size()) {
        copy(begin(v), end(v), begin(t) + n);
        for (int i = n; --i;) update(i);
    }
    void set(int p, T val) {
        assert(0 <= p && p < n);
        for (t[p += n] = val; p >>= 1;) update(p);
    }
    T operator[](int p) const {
        assert(0 <= p && p < n);
        return t[p + n];
    }
    T get(int p) const { return (*this)[p]; }
    T operator()(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        T resl = M::id(), resr = M::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = M::op(resl, t[l++]);
            if (r & 1) resr = M::op(t[--r], resr);
        }
        return M::op(resl, resr);
    }
    T prod(int l, int r) const { return (*this)(l, r); }
    T all_prod() const { return (*this)(0, n); }

  private:
    int n;
    vector<T> t;
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
};
#pragma GCC diagnostic pop

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> c(n);
    queue<int> qs;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (c[i]) qs.push(i);
    }
    vector<basic_string<int>> g(n);
    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v, u--, v--;
        g[u] += v, g[v] += u;
    }
    HLD hld(g);
    vector<int> mnd(n, 1e9), vis(n);

    while (qs.size()) {
        int v = qs.front();
        qs.pop();
        if (vis[v]) continue;
        if (c[v]) mnd[hld.in[v]] = 0;
        vis[v] = true;
        for (int u : g[v]) {
            mnd[hld.in[u]] = min(mnd[hld.in[u]], mnd[hld.in[v]] + 1);
            qs.push(u);
        }
    }

    struct Monoid {
        using T = int;
        static T id() { return 1e9; }
        static T op(T l, T r) { return min(l, r); }
    };
    SegTree<Monoid> st(mnd);
    while (q--) {
        int u, v;
        cin >> u >> v, u--, v--;
        int p = hld.lca(u, v);
        int res = 1e9;
        for (auto [l, r] : hld.path(u, p)) res = min(res, st(l, r));
        for (auto [l, r] : hld.path(v, p, 1)) res = min(res, st(l, r));
        cout << hld.dist(u, v) + 2 * res << "\n";
    }
}
