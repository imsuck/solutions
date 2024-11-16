#include <bits/stdc++.h>
using namespace std;

template<class F> struct y_comb_t {
    F f;
    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return f(*this, forward<Args>(args)...);
    }
};
template<class F> y_comb_t<decay_t<F>> y_comb(F &&f) { return {forward<F>(f)}; }

const int MXN = 5e4;
array<bitset<MXN>, MXN> dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<basic_string<int>> g(n);
    for (int i = 0, u, v; i < m; i++) cin >> u >> v, g[u - 1].push_back(v - 1);

    vector<char> vis(n);
    vector<int> ord;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        y_comb([&](auto &dfs, int v) -> void {
            vis[v] = true;
            for (int u : g[v])
                if (!vis[u]) dfs(u);
            ord.push_back(v);
        })(i);
    }
    fill_n(begin(vis), n, false);
    reverse(begin(ord), end(ord));
    for (int i : ord) {
        if (vis[i]) continue;
        y_comb([&](auto &dfs, int v) -> void {
            vis[v] = true;
            dp[v].set(v);
            for (int u : g[v]) {
                if (!vis[u]) dfs(u);
                dp[v] |= dp[u];
            }
        })(i);
    }

    for (int i = 0; i < n; i++) cout << dp[i].count() << " \n"[i == n - 1];
}
