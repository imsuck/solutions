#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<char> deg(n), vis(m);
    vector<array<int, 2>> e(m);
    vector<basic_string<int>> g(n);
    for (int i = 0; i < m; i++) {
        auto &[u, v] = e[i];
        cin >> u >> v, u--, v--;
        g[u] += i, g[v] += i;
        deg[u] ^= 1, deg[v] ^= 1;
    }
    for (auto d : deg) {
        if (d) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    vector<int> path, st{0};
    while (st.size()) {
        int v = st.back();
        if (g[v].empty()) {
            path.push_back(v), st.pop_back();
            continue;
        }
        int i = g[v].back();
        g[v].pop_back();
        if (vis[i]) continue;
        vis[i] = true;
        st.push_back(v ^ e[i][0] ^ e[i][1]);
    }
    if (path.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i <= m; i++) cout << path[i] + 1 << " \n"[i == m];
}
