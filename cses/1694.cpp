#include <bits/stdc++.h>
using namespace std;

// clang-format off
template<class T> struct Dinitz {
    Dinitz(int n) : g(n), lvl(n), iter(n) {}
 
    void add_edge(int u, int v, T cap, T rcap = 0) {
        g[u].push_back({v, int(g[v].size()), cap});
        g[v].push_back({u, int(g[u].size() - 1), rcap});
    }
 
    T max_flow(int s, int t) {
        T flow = 0;
        while (build_dag(s, t)) {
            fill(begin(iter), end(iter), 0);
            while (T f = push_flow(s, t, FLOW_INF)) flow += f;
        }
        return flow;
    }
 
  private:
    static constexpr T FLOW_INF = numeric_limits<T>::max() / 2;
 
    struct Edge {
        int to, rev;
        T cap;
    };
 
    vector<vector<Edge>> g;
    vector<int> lvl, iter;
 
    bool build_dag(int s, int t) {
        fill(begin(lvl), end(lvl), -1);
        lvl[s] = 0;
        queue<int> q; q.push(s);
        while (q.size()) {
            int v = q.front(); q.pop();
            for (auto &[to, _rev, cap] : g[v]) {
                if (lvl[to] == -1 && cap > 0) {
                    lvl[to] = lvl[v] + 1;
                    q.push(to);
                }
            }
        }
        return lvl[t] != -1;
    }
    T push_flow(int v, int t, T flow) {
        if (v == t) return flow;
        for (int &i = iter[v]; i < g[v].size(); i++) {
            auto &[to, rev, cap] = g[v][i];
            if (lvl[v] < lvl[to] && cap > 0) {
                if (T delta = push_flow(to, t, min(flow, cap))) {
                    cap -= delta, g[to][rev].cap += delta;
                    return delta;
                }
            }
        }
        return 0;
    }
};
// clang-format on

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    Dinitz<int64_t> g(n);

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        g.add_edge(a - 1, b - 1, c);
    }

    cout << g.max_flow(0, n - 1) << "\n";
}
