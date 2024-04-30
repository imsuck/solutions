#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define dbg(...)
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
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n, m;
    cin >> n >> m;
    vec<i32> g[n];
    vec<i32> col(n);
    for (i32 i = 0; i < m; i++) {
        i32 u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }

    bool ok = true;
    function<void(i32, i32)> dfs = [&](i32 v, i32 p) {
        if (col[v] == col[p] && v != p)
            return void(ok = false);
        else if (col[v] != 0)
            return;
        else
            col[v] = 1;
        col[v] = 3 - col[p];
        for (i32 u : g[v])
            dfs(u, v);
    };
    for (i32 i = 0; i < n; i++) {
        dfs(i, i);
    }
    if (!ok) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (i32 i = 0; i < n; i++) {
        cout << col[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}
