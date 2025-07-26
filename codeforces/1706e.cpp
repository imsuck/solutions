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

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    int id = n, time = 0;
    vector<basic_string<int>> g(2 * n);
    vector<int> par(2 * n), w(2 * n);
    iota(begin(par), end(par), 0);
    auto find = [&](int v) {
        while (v != par[v]) v = par[v] = par[par[v]];
        return v;
    };
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v, u--, v--;
        u = find(u), v = find(v);
        if (u == v) continue;
        par[u] = par[v] = id;
        w[id] = i + 1;
        g[id++] = {u, v};
    }
    vector<int> in(2 * n), out(2 * n);
    array<vector<int>, 18> up;
    up.fill(vector(2 * n, -1));
    y_comb([&](auto &dfs, int v, int p = -1) -> void {
        up[0][v] = p;
        for (int l = 0; l < 17 && up[l][v] != -1; l++)
            up[l + 1][v] = up[l][up[l][v]];
        in[v] = time++;
        for (int c : g[v]) dfs(c, v);
        out[v] = time;
    })(find(0));
    auto anc = [&](int p, int v) {
        return p == -1 || (in[p] <= in[v] && out[v] <= out[p]);
    };
    auto lca = [&](int u, int v) {
        if (anc(u, v)) return u;
        if (anc(v, u)) return v;
        for (int l = 17; l >= 0; l--)
            if (!anc(up[l][u], v)) u = up[l][u];
        if (up[0][u] == -1) assert(0);
        return up[0][u];
    };
    vector<int> t1(2 * n), t2(2 * n);
    auto argmin = [&](int i, int j) { return in[i] < in[j] ? i : j; };
    auto argmax = [&](int i, int j) { return in[i] > in[j] ? i : j; };
    for (int i = 0; i < n; i++) t1[i + n] = t2[i + n] = i;
    for (int i = n; --i;) {
        t1[i] = argmin(t1[i << 1], t1[i << 1 | 1]);
        t2[i] = argmax(t2[i << 1], t2[i << 1 | 1]);
    }
    auto get = [&](int l, int r) {
        int mn = l, mx = l;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) mn = argmin(mn, t1[l]), mx = argmax(mx, t2[l++]);
            if (r & 1) mn = argmin(mn, t1[--r]), mx = argmax(mx, t2[r]);
        }
        return pair(mn, mx);
    };
    while (q--) {
        int l, r;
        cin >> l >> r, l--;
        auto [u, v] = get(l, r);
        cout << w[lca(u, v)] << " \n"[!q];
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) solve();
}
