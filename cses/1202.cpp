#include <bits/stdc++.h>
using namespace std;
#include "library/other/dbg.hpp"
#include "library/other/types.hpp"

#define fn auto
template<class T> using pqueue = priority_queue<T, vec<T>, greater<>>;
auto chmin = [](auto &a, auto &&b) { return a > b ? a = b, 1 : 0; };
auto chmax = [](auto &a, auto &&b) { return a < b ? a = b, 1 : 0; };
const i64 inf = 1LL << 60;
const i32 mod = (i32)1e9 + 7;

fn solve() {
    i32 n, m;
    cin >> n >> m;
    vec<vec<pair<i32, i32>>> g(n);
    for (i32 i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w, u--, v--;
        g[u].emplace_back(v, w);
    }
    vec<i64> d(n, inf);
    vec<i32> cnt(n), mn(n, m), mx(n, 0);

    pqueue<pair<i64, i32>> q;
    cnt[0] = 1, d[0] = mn[0] = mx[0] = 0;
    q.emplace(0, 0);
    while (q.size()) {
        auto [dv, v] = q.top();
        q.pop();
        if (dv != d[v]) continue;
        for (auto [u, w] : g[v]) {
            if (chmin(d[u], dv + w)) {
                cnt[u] = cnt[v];
                mn[u] = mn[v] + 1;
                mx[u] = mx[v] + 1;
                q.emplace(d[u], u);
            } else if (d[u] == dv + w) {
                cnt[u] += cnt[v];
                if (cnt[u] >= mod) cnt[u] -= mod;
                chmin(mn[u], mn[v] + 1);
                chmax(mx[u], mx[v] + 1);
            }
        }
    }
    cout << d.back() << " " << cnt.back() << " " << mn.back() << " "
         << mx.back() << "\n";
}

fn main() -> i32 {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
