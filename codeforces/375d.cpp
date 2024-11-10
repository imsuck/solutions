#include <bits/stdc++.h>
using namespace std;

// clang-format off
template<class G> struct DsuOnTree {
    DsuOnTree(G &_g, int _root = 0)
        : g(_g), n(int(g.size())), root(_root), sz(n, 1), euler(n), in(n),
          out(n) {
        auto dfs = [&](auto &self, int v, int p) -> void {
            euler[time] = v, in[v] = time++;
            if (g[v].size() && g[v][0] == p) swap(g[v][0], g[v].back());
            for (int &c : g[v]) {
                if (c == p) continue;
                self(self, c, v), sz[v] += sz[c];
                if (sz[g[v][0]] < sz[c]) swap(g[v][0], c);
            }
            out[v] = time;
        };
        dfs(dfs, root, -1);
    }

    template<class F1, class F2, class F3>
    void run(F1 &&add, F2 &&del, F3 &&query) {
        auto dfs = [&](auto &self, int v, int p, bool keep) -> void {
            for (int c : g[v]) if (c != p && c != g[v][0]) self(self, c, v, false);
            if (g[v].size() && g[v][0] != p) self(self, g[v][0], v, true);
            for (int c : g[v]) {
                if (c == p || c == g[v][0]) continue;
                for (int i = in[c]; i < out[c]; i++) add(euler[i]);
            }
            add(v), query(v);
            if (!keep) for (int i = in[v]; i < out[v]; i++) del(euler[i]);
        };
        dfs(dfs, root, -1, false);
    }

  private:
    G &g;
    int n, root, time = 0;
    vector<int> sz, euler, in, out;
};
// clang-format on

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
template<class M> struct SegTree {
    using T = typename M::T;
    SegTree(int _n) : n(_n), t(n * 2, M::id()) {}

    void set(int p, T val) {
        assert(0 <= p && p < n);
        for (t[p += n] = val; p >>= 1;) update(p);
    }
    T operator[](int p) const {
        assert(0 <= p && p < n);
        return t[p + n];
    }
    T operator()(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        T resl = M::id(), resr = M::id();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = M::op(resl, t[l++]);
            if (r & 1) resr = M::op(t[--r], resr);
        }
        return M::op(resl, resr);
    }

  private:
    int n;
    vector<T> t;
    void update(int p) { t[p] = M::op(t[p << 1], t[p << 1 | 1]); }
};
#pragma GCC diagnostic pop

struct AddMonoid {
    using T = int;
    static T id() { return 0; }
    static T op(T l, T r) { return l + r; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<int> color(n);
    for (int i = 0; i < n; i++) cin >> color[i], color[i]--;

    vector<basic_string<int>> g(n);
    for (int i = 0, u, v; i < n - 1; i++)
        cin >> u >> v, g[--u].push_back(--v), g[v].push_back(u);

    vector<vector<pair<int, int>>> queries(n + 1);

    for (int i = 0, v, x; i < q; i++)
        cin >> v >> x, queries[v - 1].emplace_back(x, i);

    vector<int> cnt(100'001);
    SegTree<AddMonoid> st(100'001);
    vector<int> ans(q);
    auto add = [&](int v) {
        int &cur = cnt[color[v]];
        st.set(cur, st[cur] - 1);
        cur++;
        st.set(cur, st[cur] + 1);
    };
    auto del = [&](int v) {
        int &cur = cnt[color[v]];
        st.set(cur, st[cur] - 1);
        cur--;
        st.set(cur, st[cur] + 1);
    };
    auto query = [&](int v) {
        for (auto [x, i] : queries[v]) ans[i] = x <= n ? st(x, n + 1) : 0;
    };

    DsuOnTree solver(g);

    solver.run(add, del, query);

    for (int i : ans) cout << i << "\n";
}
