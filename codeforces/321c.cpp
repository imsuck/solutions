#include <bits/stdc++.h>
using namespace std;

// clang-format off
template<class Graph>
pair<Graph, int> shallowest_decomp(const Graph &g, int root = 0) {
    auto clz = [](uint32_t x) { return x ? __builtin_clz(x) : 32; };
    auto ctz = [](uint32_t x) { return x ? __builtin_ctz(x) : 32; };
    auto bw = [&](uint32_t x) { return clz(0) - clz(x); };
    const int n = int(g.size());
    Graph tree(n), st(bw(n));

    auto chain = [&](int labels, int v) {
        while (labels) {
            int label = __lg(labels);
            labels ^= 1 << label;
            int c = st[label].back(); st[label].pop_back();
            tree[v].push_back(c);
            v = c;
        }
    };
    vector<int> forbid(n, -1);
    auto dfs = [&](auto &self, int v, int p = -1) -> void {
        int once = 0, twice = 0;
        for (int c : g[v]) {
            if (c == p) continue;
            self(self, c, v);
            twice |= once & (forbid[c] + 1);
            once |= forbid[c] + 1;
        }
        forbid[v] = once | ((1 << bw(twice)) - 1);
        int label = ctz(forbid[v] + 1);
        st[label].push_back(v);
        for (int i = int(g[v].size()) - 1; i >= 0; i--) {
            int c = g[v][i];
            chain((forbid[c] + 1) & ((1 << label) - 1), v);
        }
    };
    dfs(dfs, root);
    int mx = __lg(forbid[root] + 1);
    int nroot = st[mx].back(); st[mx].pop_back();
    chain((forbid[root] + 1) & ((1 << mx) - 1), nroot);
    return {move(tree), nroot};
}
// clang-format on

template<class F> struct y_comb_t {
    F f;
    template<class... Args> decltype(auto) operator()(Args &&...args) {
        return f(/* ref */(*this), forward<Args>(args)...);
    }
};
template<class F> y_comb_t<decay_t<F>> y_comb(F &&f) { return {forward<F>(f)}; }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<basic_string<int>> g(n);
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        g[--u].push_back(--v), g[v].push_back(u);
    }
    auto [tree, root] = shallowest_decomp(g);
    vector<char> label(n);
    label[root] = 'A';
    y_comb([&](auto &dfs, int v) -> void {
        for (int c : tree[v]) label[c] = label[v] + 1, dfs(c);
    })(root);
    for (int i = 0; i < n; i++) cout << label[i] << " \n"[i == n - 1];
}
