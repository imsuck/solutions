#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
    #define dbg(...) (void(0))
    #define debug() if (0)
#endif

struct RollbackDSU {
    int n, cc;
    vector<int> data;
    stack<pair<int &, int>> his;

    RollbackDSU() {}
    RollbackDSU(int _n) : n(_n), cc(n), data(n, -1) {}

    int find(int v) { return data[v] < 0 ? v : find(data[v]); }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        his.emplace(cc, n + 1);
        if (u == v) return;
        if (data[u] > data[v]) swap(u, v);
        his.emplace(cc, cc);
        his.emplace(data[u], data[u]);
        his.emplace(data[v], data[v]);
        cc--;
        data[u] += exchange(data[v], u);
    }
    void undo() {
        assert(!his.empty());
        while (true) {
            auto [a, b] = his.top();
            his.pop();
            if (b == n + 1) break;
            a = b;
        }
    }
};

auto minmax(int a, int b) { return pair(min(a, b), max(a, b)); }

struct OfflineDynamicConnectivity {
    OfflineDynamicConnectivity(int _n, int _m) : n(_n), m(_m) {}

    void link(int u, int v) {
        time++;
        auto edge = minmax(u, v);
        open.emplace(edge, time);
    }
    void cut(int u, int v) {
        time++;
        auto edge = minmax(u, v);
        auto it = open.find(edge);
        assert(it != open.end());
        closed.emplace_back(edge.first, edge.second, it->second, time);
        open.erase(it);
    }
    auto run() {
        time++;
        for (auto [edge, s] : open) {
            closed.emplace_back(edge.first, edge.second, s, time);
        }

        int size = bit_ceil(time);
        vector<vector<pair<int, int>>> edges(2 * size);
        for (auto [u, v, l, r] : closed) {
            for (l += size, r += size; l < r; l /= 2, r /= 2) {
                if (l & 1) edges[l++].emplace_back(u, v);
                if (r & 1) edges[--r].emplace_back(u, v);
            }
        }

        vector<int> ret;
        RollbackDSU dsu(n);
        auto dfs = [&](auto &f, int k) -> void {
            for (auto [u, v] : edges[k]) dsu.merge(u, v);
            if (k < size) {
                f(f, 2 * k), f(f, 2 * k + 1);
            } else if (k < size + time) {
                if (k - size >= m) ret.push_back(dsu.cc);
            }
            for (int i = 0; i < edges[k].size(); i++) dsu.undo();
        };
        dfs(dfs, 1);
        return ret;
    }

  private:
    int n, m, time = 0;
    map<pair<int, int>, int> open;
    vector<tuple<int, int, int, int>> closed;
    // clang-format off
    static int bit_ceil(int n) { int m = 1; while (m < n) m *= 2; return m; }
    // clang-format on
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    OfflineDynamicConnectivity dc(n, m);
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v, u--, v--;
        dc.link(u, v);
    }
    for (int i = 0, t, u, v; i < k; i++) {
        cin >> t >> u >> v, u--, v--;
        if (t == 1) {
            dc.link(u, v);
        } else {
            dc.cut(u, v);
        }
    }
    auto ret = dc.run();
    for (int cc : ret) cout << cc << " ";
    cout << "\n";
}
