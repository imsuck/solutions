#include <bits/stdc++.h>
using namespace std;
 
template<class M> struct Rerooting {
    using T = typename M::T;
    using Cost = typename M::Cost;
 
    Rerooting(int n) : g(n), dp_sub(n, M::id()), dp_all(n) {}
    void add_edge(int u, int v, const Cost &c) {
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }
 
    template<class F, class G> auto run(F &&_f, G &&_g) {
        apply_edge = _f, apply_vertex = _g;
        dfs_sub(0, -1), dfs_all(0, -1, M::id());
        return dp_all;
    }
 
  private:
    vector<vector<pair<int, Cost>>> g;
    function<T(T, int, int, Cost)> apply_edge;
    function<T(T, int)> apply_vertex;
    vector<T> dp_sub, dp_all;
    void dfs_sub(int v, int p) {
        for (const auto &[c, cost] : g[v]) {
            if (c == p) continue;
            dfs_sub(c, v);
            dp_sub[v] = M::op(dp_sub[v], apply_edge(dp_sub[c], v, c, cost));
        }
        dp_sub[v] = apply_vertex(dp_sub[v], v);
    }
    void dfs_all(int v, int p, const T &val) {
        vector ds = {val};
        for (const auto &[c, cost] : g[v]) {
            if (c == p) continue;
            ds.push_back(apply_edge(dp_sub[c], v, c, cost));
        }
        int n = int(ds.size());
        vector head(n + 1, M::id()), tail(n + 1, M::id());
        for (int i = 0; i < n; i++) head[i + 1] = M::op(head[i], ds[i]);
        for (int i = n; i--;) tail[i] = M::op(ds[i], tail[i + 1]);
        dp_all[v] = apply_vertex(head[n], v);
        int k = 1;
        for (const auto &[c, cost] : g[v]) {
            if (c == p) continue;
            dfs_all(c, v,
                    apply_edge(apply_vertex(M::op(head[k], tail[k + 1]), v), c,
                               v, cost));
            k++;
        }
    }
};
 
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
 
    struct M {
        using T = int;
        using Cost = int;
        static T id() { return 0; }
        static T op(T l, T r) { return max(l, r); }
    };
    Rerooting<M> reroot(n);
    for (int i = 0, u, v; i < n - 1; i++)
        cin >> u >> v, reroot.add_edge(u - 1, v - 1, 1);
 
    auto ans = reroot.run(
        [](M::T x, int, int, M::Cost c) { return x + c; },
        [](M::T x, int) -> M::T { return x; }
    );
    for (int i = 0; i < n; i++) 
        cout << ans[i] << " \n"[i == n - 1];
}
