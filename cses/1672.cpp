#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;
using u64 = uint64_t;

u64 dist[500][500];
const u64 inf = -1;

int main() {
    memset(dist, -1, sizeof dist);
    for (int i = 0; i < 500; i++) dist[i][i] = 0;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, q;
    cin >> n >> m >> q;
    for (size_t i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w, u--, v--;
        dist[u][v] = dist[v][u] = min(dist[v][u], w);
    }
    for (int i = 0; i < n; i++) {
        for (int v = 0; v < n; v++) {
            for (int u = 0; u < n; u++) {
                if (dist[u][i] == inf || dist[i][v] == inf) continue;
                dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
            }
        }
    }
    while (q--) {
        int u, v;
        cin >> u >> v, u--, v--;
        cout << (i64)dist[u][v] << "\n";
    }
}
