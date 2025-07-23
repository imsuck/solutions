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

struct TwoSAT {
    int n;
    vector<basic_string<int>> g;

    TwoSAT(int _n) : n(_n), g(2 * n) {}

    void add_if(int x, int y) { g[x] += y, g[neg(y)] += neg(x); }
    void add_or(int x, int y) { add_if(neg(x), y); }
    void add_nand(int x, int y) { add_if(x, neg(y)); }
    void set_true(int x) { add_if(x, neg(x)); }
    void set_false(int x) { add_if(neg(x), x); }

    vector<bool> run() {
        vector<bool> res(n);
        auto [scc, rep, gd] = condense(g);
        for (int i = 0; i < n; i++) {
            if (rep[i] == rep[neg(i)]) return {};
            res[i] = rep[i] > rep[neg(i)];
        }
        return res;
    }

    int neg(int x) { return x < n ? x + n : x - n; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> m >> n;
    TwoSAT solver(n);
    while (m--) {
        int a, b;
        char na, nb;
        cin >> na >> a >> nb >> b, a--, b--;
        a = na == '+' ? a : solver.neg(a);
        b = nb == '+' ? b : solver.neg(b);
        solver.add_or(a, b);
    }
    auto res = solver.run();
    if (res.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < n; i++)
        cout << (res[i] ? '+' : '-') << " \n"[i == n - 1];
}
