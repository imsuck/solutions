#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...) 42
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) begin(a), end(a)
#define rall(a) rbegin(a), rend(a)
#define pb push_back
#define pp pop_back
#define eb emplace_back

template<class Fn> struct add_recursion_t {
    Fn fn;
    template<class... Args> auto operator()(Args &&...args) {
        return fn(*this, args...);
    }
};
template<class Fn> auto make_recur(Fn &&f) { return add_recursion_t<Fn>{f}; }

void solve() {
    i32 n;
    cin >> n;
    vec<i32> c(n);
    for (i32 i = 0; i < n; i++) {
        cin >> c[i];
    }
    vec<vec<i32>> g(n);
    for (i32 i = 0; i < n - 1; i++) {
        i32 u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    vec<set<i32>> cnt(n);
    vec<i32> distinct(n);
    auto dfs = make_recur([&](auto &&self, i32 v, i32 p = -1) -> void {
        cnt[v].insert(c[v]);
        for (i32 u : g[v]) {
            if (u != p) {
                self(u, v);
                if (cnt[v].size() < cnt[u].size()) swap(cnt[v], cnt[u]);
                cnt[v].insert(all(cnt[u]));
            }
        }
        distinct[v] = (i32)cnt[v].size();
    });
    dfs(0);
    for (i32 i = 0; i < n; i++) {
        cout << distinct[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--) solve();
}
