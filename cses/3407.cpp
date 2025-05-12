#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p;

    DSU(int _n) : n(_n), p(n, -1) {}

    int find(int v) { return p[v] < 0 ? v : p[v] = find(p[v]); }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (p[u] > p[v]) swap(u, v);
        p[u] += p[v];
        p[v] = u;
        return true;
    }
    bool same(int u, int v) { return find(u) == find(v); }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    struct edge {
        int u, v, w;
    };
    vector<edge> es(m);
    for (int i = 0; i < m; i++) {
        auto &[u, v, w] = es[i];
        cin >> u >> v >> w, u--, v--;
    }

    vector<int> id(m);
    iota(begin(id), end(id), 0);
    sort(begin(id), end(id), [&](int i, int j) { return es[i].w < es[j].w; });
    id.push_back(-69);

    vector<char> ok(m);
    vector<int> bin;
    DSU dsu(n);
    int prv = id[0];
    for (int i : id) {
        if (i == -69 || es[i].w != es[prv].w) {
            for (auto x : bin) ok[x] = !dsu.same(es[x].u, es[x].v);
            for (auto &x : exchange(bin, {})) dsu.merge(es[x].u, es[x].v);
            prv = i;
        }
        if (i != -69) bin.push_back(i);
    }

    for (auto b : ok) cout << (b ? "YES" : "NO") << "\n";
}
