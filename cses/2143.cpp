#include <bits/stdc++.h>
using namespace std;

template<class G> auto find_scc(const G &g) {
    int n = int(g.size());
    vector<int> val(n), z;
    vector<char> added(n);
    vector<basic_string<int>> scc;
    int time = 0;
    auto dfs = [&](auto &self, int v) -> int {
        int low = val[v] = time++;
        z.push_back(v);
        for (auto u : g[v])
            if (!added[u]) low = min(low, val[u] ?: self(self, u));
        if (low == val[v]) {
            scc.emplace_back();
            int x;
            do {
                x = z.back(); z.pop_back();
                added[x] = true;
                scc.back().push_back(x);
            } while (x != v);
        }
        return val[v] = low;
    };
    for (int i = 0; i < n; i++)
        if (!added[i]) dfs(dfs, i);
    reverse(begin(scc), end(scc));
    return scc;
}
template<class G> auto condense(const G &g) {
    auto scc = find_scc(g);
    int n = int(scc.size());
    vector<int> rep(g.size());
    for (int i = 0; i < n; i++)
        for (auto v : scc[i]) rep[v] = i;
    vector<basic_string<int>> gd(n);
    for (int v = 0; v < g.size(); v++)
        for (auto u : g[v])
            if (rep[v] != rep[u]) gd[rep[v]].push_back(rep[u]);
    for (int i = 0; i < n; i++) {
        sort(begin(gd[i]), end(gd[i]));
        gd[i].erase(unique(begin(gd[i]), end(gd[i])), end(gd[i]));
    }
    return make_tuple(scc, rep, gd);
}

const int MXN = 5e4;
array<bitset<MXN>, MXN> dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, q;
    cin >> n >> m >> q;
    vector<basic_string<int>> g(n);
    for (int i = 0, u, v; i < m; i++) cin >> u >> v, g[u - 1].push_back(v - 1);

    auto [scc, rep, gd] = condense(g);

    vector<char> vis(gd.size());
    auto dfs = [&](auto &self, int v) -> void {
        vis[v] = true;
        dp[v].set(v);
        for (int u : gd[v]) {
            if (!vis[u]) self(self, u);
            dp[v] |= dp[u];
        }
    };
    for (int i = 0; i < gd.size(); i++)
        if (!vis[i]) dfs(dfs, i);

    while (q--) {
        int u, v;
        cin >> u >> v;
        u = rep[u - 1], v = rep[v - 1];
        cout << (dp[u][v] ? "YES" : "NO") << "\n";
    }
}
