#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) 42
#endif

using i32 = int32_t;
using i64 = int64_t;
#define vec vector

struct Graph {
    int sz;

    Graph(int n) : sz(n), g(sz) {}
    void add_edge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }
    vector<int> &operator[](int i) { return g[i]; }
    const vector<int> &operator[](int i) const { return g[i]; }

  private:
    vector<vector<int>> g;
};

struct EulerTour {
    int t = 0;
    vector<int> tin, tout;
    EulerTour(const Graph &g, int root = 0) : tin(g.sz), tout(g.sz) {
        auto dfs = [&](auto self, int v, int p = -1) -> void {
            tin[v] = t++;
            for (int u : g[v])
                if (u != p)
                    self(self, u, v);
            tout[v] = t;
        };
        dfs(dfs, root);
    }
};

template<class M, class S = typename M::S> struct SegTree {
    SegTree(int _n) : n(_n), t(n * 2, M::e) {}
    SegTree(const vector<S> &v) : SegTree(int(v.size())) {
        copy(begin(v), end(v), begin(t) + n);
        for (int i = n - 1; i > 0; i--) update(i);
    }

    void set(int p, const S &x) { for (t[p += n] = x; p >>= 1;) update(p); }
    S get(int p) const { return t[p + n]; }
    S prod(int l, int r) const {
        if (l == r) return M::e;
        S sml = M::e, smr = M::e;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = M::op(sml, t[l++]);
            if (r & 1) smr = M::op(t[--r], smr);
        }
        return M::op(sml, smr);
    }

    int n;
    vector<S> t;
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
};

struct M {
    using S = i64;
    static inline S e = 0;
    static inline plus<> op{};
};

void solve() {
    i32 n, q;
    cin >> n >> q;
    vec<i64> vals(n);
    for (i64 &i : vals) {
        cin >> i;
    }
    Graph g(n);
    for (i32 i = 0; i < n - 1; i++) {
        i32 u, v;
        cin >> u >> v, g.add_edge(u - 1, v - 1);
    }
    EulerTour tour(g);
    vec<i64> init(n);
    for (i32 i = 0; i < n; i++) {
        init[tour.tin[i]] = vals[i];
    }
    SegTree<M> st(init);
    while (q--) {
        i32 qt, s, x;
        cin >> qt >> s;
        s--;
        if (qt == 1) {
            cin >> x;
            st.set(tour.tin[s], x);
        } else if (qt == 2) {
            cout << st.prod(tour.tin[s], tour.tout[s]) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    while (t--) solve();
}
