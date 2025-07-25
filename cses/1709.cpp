#include <bits/stdc++.h>
using namespace std;

// clang-format off
template<class T> struct Dinitz {
    Dinitz() {}
    Dinitz(int n) : g(n), lvl(n), iter(n) {}

    void add_edge(int u, int v, T cap, T rcap = 0) {
        g[u].push_back({v, (int)g[v].size(), cap});
        g[v].push_back({u, (int)g[u].size() - 1, rcap});
    }

    T max_flow(int s, int t) {
        T flow = 0;
        while (build_dag(s, t)) {
            fill(begin(iter), end(iter), 0);
            while (T f = push_flow(s, t, FLOW_INF)) flow += f;
        }
        return flow;
    }
    set<int> min_cut(int s) {
        stack<int> st;
        set<int> vis;
        st.push(s);
        vis.insert(s);
        while (st.size()) {
            int v = st.top();
            st.pop();
            for (auto &[to, rev, cap] : g[v]) 
                if (cap && !vis.count(to)) 
                    vis.insert(to), st.push(to);
        }
        return vis;
    }

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
    int n;
    cin >> n;
    Dinitz<int> g(2 * n + 2);
    for (int i = 1; i <= n; i++) {
        g.add_edge(0, i, 1);
        g.add_edge(i + n, 2 * n + 1, 1);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if (c == 'o') g.add_edge(i, j + n, 1e5);
        }
    }
    cout << g.max_flow(0, 2 * n + 1) << "\n";
    auto cut = g.min_cut(0);
    for (int v : cut) {
        for (auto &[u, rev, cap] : g.g[v]) {
            if (!cut.count(u)) {
                if (v == 0) {
                    cout << "1 " << u << "\n";
                } else if (u == 2 * n + 1) {
                    cout << "2 " << v - n << "\n";
                }
            }
        }
    }
}
