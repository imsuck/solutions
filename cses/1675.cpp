#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
using i64 = int64_t;
#define vec vector
#define all(a) (a).begin(), (a).end()

struct Edge {
    i32 v, u;
    i64 w;
    bool operator<(const Edge &other) { return w < other.w; }
    void operator!() { cin >> v >> u >> w, v--, u--; }
};

struct Dsu {
    vec<i32> dsu, sz;
    i32 cc;
    Dsu(i32 n) : dsu(n), sz(n, 1), cc(n) {
        for (i32 i = 0; i < n; i++) {
            dsu[i] = i;
        }
    }
    i32 find(i32 v) {
        if (v == dsu[v]) {
            return v;
        }
        return dsu[v] = find(dsu[v]);
    }
    void merge(i32 a, i32 b) {
        a = find(a), b = find(b);
        if (a == b) {
            return;
        }
        if (sz[a] < sz[b]) {
            swap(a, b);
        }
        cc--;
        dsu[b] = a;
        sz[a] += sz[b];
    }
};

void solve() {
    i32 n, m;
    cin >> n >> m;
    vec<Edge> edges(m);
    for (Edge &edge : edges) {
        !edge;
    }
    sort(all(edges));
    i64 weight = 0;
    Dsu dsu(n);
    for (Edge edge : edges) {
        if (dsu.find(edge.v) == dsu.find(edge.u)) {
            continue;
        }
        weight += edge.w;
        dsu.merge(edge.v, edge.u);
    }
    if (dsu.cc != 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    cout << weight << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
