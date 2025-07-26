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
    int n, q;
    cin >> n >> q;
    vector<int> f(n), vis(n, n), dep(n), len(n), dist(n), hd(n);
    vector<basic_string<int>> fp(n);
    for (int i = 0, x; i < n; i++) {
        cin >> x, x--;
        f[i] = x, fp[x] += i;
    }
    int time = 0;
    auto dfs = y_comb([&](auto &self, int v) -> int {
        vis[v] = time;
        int u = f[v];
        if (vis[u] == vis[v]) {
            int length = dep[v] - dep[u] + 1;
            len[v] = length, hd[v] = v;
            return length - 1;
        } else if (vis[u] < vis[v]) {
            dist[v] = dist[u] + 1, len[v] = len[u], hd[v] = hd[u];
            return 0;
        } else {
            dep[u] = dep[v] + 1;
            int c = self(u);
            if (c > 0) {
                len[v] = len[u], hd[v] = v;
                return c - 1;
            } else {
                dist[v] = dist[u] + 1, len[v] = len[u], hd[v] = hd[u];
                return 0;
            }
        }
    });
    for (int v = 0; v < n; v++, time++)
        if (vis[v] == n) dfs(v);
    time = 0;
    vector<int> in(n, n), out(n);
    auto dfs2 = y_comb([&](auto &self, int v) -> void {
        in[v] = time++;
        for (int u : fp[v])
            if (in[u] == n) self(u);
        out[v] = time;
    });
    for (int v = 0; v < n; v++)
        if (!dist[v] && in[v] == n) dfs2(v);
    auto anc = [&](int p, int v) { return in[p] <= in[v] && out[v] <= out[p]; };
    while (q--) {
        int a, b;
        cin >> a >> b, a--, b--;
        int ha = hd[a], hb = hd[b];
        if (vis[ha] != vis[hb] || (!dist[a] && dist[b]) ||
            (dist[a] && dist[b] && !anc(b, a))) {
            cout << "-1\n";
            continue;
        }
        if (!dist[a] && !dist[b]) {
            cout << (dep[b] - dep[a] + len[a]) % len[a] << "\n";
        } else if (dist[a] && !dist[b]) {
            cout << dist[a] + (dep[b] - dep[ha] + len[b]) % len[b] << "\n";
        } else {
            cout << dist[a] - dist[b] << "\n";
        }
    }
}
