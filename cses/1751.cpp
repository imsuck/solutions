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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> f(n), in(n, n), dep(n), len(n), dist(n);
    for (int &i : f) cin >> i, i--;

    int time = 0;
    auto dfs = y_comb([&](auto &self, int v) -> int {
        in[v] = time;
        int u = f[v];
        if (in[u] == in[v]) { // found cycle
            int length = dep[v] - dep[u] + 1;
            len[v] = length;
            return length - 1; // don't count self
        } else if (in[u] < in[v]) {
            dist[v] = dist[u] + 1;
            len[v] = len[u];
            return 0;
        } else {
            dep[u] = dep[v] + 1;
            int c = self(u);
            if (c > 0) { // in cycle
                len[v] = len[u];
                return c - 1;
            } else {
                dist[v] = dist[u] + 1;
                len[v] = len[u];
                return 0;
            }
        }
    });
    for (int i = 0; i < n; i++, time++)
        if (in[i] == n) dfs(i);
    for (int i = 0; i < n; i++) cout << dist[i] + len[i] << " \n"[i == n - 1];
}
