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

void dfs(i32 v, vec<i32> g[], vec<bool> &vis, i32 &cnt) {
    if (vis[v]) return;
    vis[v] = true;
    cnt++;
    for (i32 u : g[v]) {
        dfs(u, g, vis, cnt);
    }
}

void solve() {
    i32 n, m;
    cin >> n >> m;
    vec<i32> g1[n], g2[n];
    i32 cnt1 = 0, cnt2 = 0;
    vec<bool> vis1(n), vis2(n);
    for (i32 i = 0; i < m; i++) {
        i32 u, v;
        cin >> u >> v;
        u--, v--;
        g1[u].pb(v);
        g2[v].pb(u);
    }
    dfs(0, g1, vis1, cnt1);
    dfs(0, g2, vis2, cnt2);
    if (cnt1 == n && cnt2 == n) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
    for (i32 i = 1; i < n; i++) {
        if (!vis1[i]) {
            cout << "1 " << i + 1 << "\n";
            return;
        }
        if (!vis2[i]) {
            cout << i + 1 << " 1\n";
            return;
        }
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
