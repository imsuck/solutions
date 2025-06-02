#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, sz, wg;

    DSU(int _n) : n(_n), p(n), sz(n, 1), wg(n, 1.1e9) {
        iota(begin(p), end(p), 0);
    }

    int find(int v) const { return v == p[v] ? v : find(p[v]); }
    bool merge(int u, int v, int w) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v], p[v] = u;
        wg[v] = w;
        return true;
    }
    int max_edge(int u, int v) const {
        for (;; u = p[u]) {
            if (wg[u] > wg[v]) swap(u, v);
            if (p[u] == v) return wg[u];
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;

    int64_t cost = 0;
    DSU dsu(n);
    vector<array<int, 3>> edges(m);
    for (int i = 0; i < m; i++) {
        auto &[u, v, w] = edges[i];
        cin >> u >> v >> w, u--, v--;
    }

    vector<int> id(m);
    iota(begin(id), end(id), 0);
    sort(begin(id), end(id), [&](int i, int j) {
        return edges[i][2] < edges[j][2];
    });
    for (int i : id) {
        auto [u, v, w] = edges[i];
        cost += dsu.merge(u, v, w) ? w : 0;
    }
    for (int i = 0; i < m; i++) {
        auto [u, v, w] = edges[i];
        cout << cost + w - dsu.max_edge(u, v) << "\n";
    }
}
