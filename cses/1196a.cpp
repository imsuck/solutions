#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto
const i64 inf = 1LL << 60;
template<class T> using pqueue = priority_queue<T, vec<T>, greater<>>;
auto chmin = [](auto &a, auto &&b) { return a > b ? a = b, 1 : 0; };

fn solve() {
    i32 n, m, k;
    cin >> n >> m >> k;

    vec<vec<pair<i32, i32>>> g(n);
    for (i32 i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w, u--, v--;
        g[u].emplace_back(v, w);
    }

    auto push = [&](auto &v, i64 i) {
        auto it = upper_bound(begin(v), end(v), i);
        i32 r = (i32)(it - begin(v));
        v.insert(it, i), v.pop_back();
        return r;
    };
    vec<vec<i64>> d(n, vec<i64>(k, inf));
    pqueue<tuple<i64, i32, i32>> q;
    d[0][0] = 0;
    q.emplace(0, 0, 0);
    while (q.size()) {
        auto [dv, v, t] = q.top();
        q.pop();
        if (find(begin(d[v]), end(d[v]), dv) == end(d[v])) continue;
        for (auto [u, w] : g[v]) {
            i32 pos = push(d[u], dv + w);
            if (pos < k) q.emplace(d[u][pos], u, pos);
        }
    }
    for (i64 i : d.back()) cout << i << " ";
    cout << "\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
