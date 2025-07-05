#include <bits/stdc++.h>
using namespace std;

template<class F> struct y_comb_t {
    F f;
    template<class... Ts> decltype(auto) operator()(Ts &&...args) {
        return f(*this, forward<Ts>(args)...);
    }
};
template<class F> y_comb_t<decay_t<F>> y_comb(F &&f) { return {forward<F>(f)}; }

#ifndef LOCAL
    #define dbg(...) (void(0))
#endif

#define fn auto
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using str = string;
template<class T> using vec = vector<T>;

fn solve() {
    i32 n, m;
    cin >> n >> m;
    vec<basic_string<i32>> g(n);
    vec<array<i32, 2>> ed(m);
    vec<bool> used(m);
    for (i32 i = 0, u, v; i < m; i++) {
        cin >> u >> v, u--, v--;
        g[u] += i, g[v] += i;
        ed[i] = {u, v};
    }

    i32 time = 0;
    vec<i32> in(n, n), low(n, n);
    vec<pair<i32, i32>> ans;
    bool has_bridge = false;
    ans.reserve(m);
    y_comb([&](auto &self, i32 v, i32 p) -> void {
        low[v] = in[v] = time++;
        for (i32 e : g[v]) {
            i32 u = ed[e][0] ^ ed[e][1] ^ v;
            if (u == p) continue;
            if (in[u] < n) {
                if (!used[e]) ans.emplace_back(v, u), used[e] = true;
                low[v] = min(low[v], in[u]);
            } else {
                ans.emplace_back(v, u), used[e] = true;
                self(u, v);
                low[v] = min(low[v], low[u]);
            }
        }
        if (p != -1 && low[v] >= in[v]) has_bridge = true;
    })(0, -1);

    if (time < n || has_bridge) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (auto [u, v] : ans) cout << u + 1 << " " << v + 1 << "\n";
}

fn main() -> i32 {
    cin.tie(nullptr)->sync_with_stdio(false);
    i32 t = 1;
    // cin >> t;
    while (t--) solve();
}
