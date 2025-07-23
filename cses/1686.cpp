#include <bits/stdc++.h>
using namespace std;

template<class G> auto find_scc(const G &g) {
    int n = g.size();
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
                x = z.back(), z.pop_back();
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
    int n = scc.size();
    vector<int> rep(g.size());
    for (int i = 0; i < n; i++)
        for (auto v : scc[i]) rep[v] = i;
    vector<basic_string<int>> gd(n);
    for (int v = 0; v < g.size(); v++)
        for (auto u : g[v])
            if (rep[v] != rep[u]) gd[rep[v]].push_back(rep[u]);
    for (auto &v : gd) {
        sort(begin(v), end(v));
        v.erase(unique(begin(v), end(v)), end(v));
    }
    return make_tuple(move(scc), move(rep), move(gd));
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    vector<basic_string<int>> g(n);
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v, u--, v--;
        g[u] += v;
    }
    auto [scc, rep, gd] = condense(g);
    int k = scc.size();
    vector<int64_t> dp(k);
    for (int i = 0; i < n; i++) dp[rep[i]] += a[i];
    for (int v = k - 1; v >= 0; v--) {
        int64_t mx = 0;
        for (int u : gd[v]) mx = max(mx, dp[u]);
        dp[v] += mx;
    }
    cout << *max_element(begin(dp), end(dp)) << "\n";
}
