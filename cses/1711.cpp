#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"
#include "library/other/y_combinator.hpp"

#define fn auto
template<class T> using pqueue = priority_queue<T, vec<T>, greater<>>;

fn solve() {
    struct edge {
        i32 to, cap, rev, real;
    };

    i32 n, m;
    cin >> n >> m;

    vec<vec<edge>> g(n);
    for (i32 i = 0, u, v; i < m; i++) {
        cin >> u >> v, u--, v--;
        g[u].push_back({v, 1, (i32)g[v].size(), 1});
        g[v].push_back({u, 0, (i32)g[u].size() - 1, 0});
    }

    vec<i32> lvl(n), iter(n);
    auto bfs = [&](i32 s, i32 t) {
        fill_n(begin(lvl), n, -1);
        queue<i32> q;
        lvl[s] = 0, q.push(s);
        while (q.size()) {
            i32 v = q.front();
            q.pop();
            for (auto &[to, cap, rev, r] : g[v]) {
                if (!cap || lvl[to] != -1) continue;
                lvl[to] = lvl[v] + 1;
                q.push(to);
            }
        }
        return lvl[t] != -1;
    };
    auto dfs = y_comb([&](auto &self, i32 v, i32 t, i32 f = 1e5) -> i32 {
        if (v == t) return f;
        for (i32 &i = iter[v]; i < g[v].size(); i++) {
            auto &[to, cap, rev, r] = g[v][i];
            if (!cap || lvl[to] <= lvl[v]) continue;
            if (i32 delta = self(to, t, min(f, cap))) {
                cap -= delta;
                g[to][rev].cap += delta;
                return delta;
            }
        }
        return 0;
    });

    i32 cnt = 0;
    while (bfs(0, n - 1)) {
        fill_n(begin(iter), n, 0);
        while (i32 d = dfs(0, n - 1)) cnt += d;
    }
    cout << cnt << "\n";
    auto get_path = [&](i32 v, i32 t) {
        vec<i32> path{0};
        for (;;) {
            path.push_back(v);
            if (v == t) break;
            for (auto &e : g[v]) {
                if (!e.cap && e.real) {
                    v = e.to, e.real = 0;
                    break;
                }
            }
        }
        return path;
    };
    for (auto &e : g[0]) {
        if (e.cap || !e.real) continue;
        auto path = get_path(e.to, n - 1);
        cout << path.size() << "\n";
        for (i32 i : path) cout << i + 1 << " ";
        cout << "\n";
    }
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
