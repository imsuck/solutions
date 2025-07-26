#include <bits/stdc++.h>
using namespace std;

template<class F> struct y_comb_t {
    F f;
    template<class T> y_comb_t(T &&_f) : f(forward<T>(_f)) {}
    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return f(/* ref */ (*this), forward<Args>(args)...);
    }
};
template<class F> y_comb_t<decay_t<F>> y_comb(F &&f) { return {forward<F>(f)}; }

const int mod = (int)1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> dp(n, -1);
    dp[n - 1] = 1;
    vector<basic_string<int>> g(n);
    for (int i = 0, u, v; i < m; i++) cin >> u >> v, g[u - 1] += v - 1;
    y_comb([&](auto &f, int v = 0) -> int {
        if (dp[v] != -1) return dp[v];
        dp[v] = 0;
        for (int u : g[v]) dp[v] += f(u), dp[v] -= (dp[v] >= mod) * mod;
        return dp[v];
    })();
    cout << dp[0] << "\n";
}
