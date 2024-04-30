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
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define pb push_back
#define pp pop_back
#define eb emplace_back

template<typename T> using pq = priority_queue<T, vector<T>, greater<T>>;

vec<vec<i32>> g;
vec<i32> low, tin;
vec<bool> vis;
set<i32> cutpoints;
i32 timer = 0, bridges = 0;

void dfs(i32 v, i32 p = -1) {
    low[v] = tin[v] = timer++;
    vis[v] = true;
    i32 children = 0;
    for (i32 to : g[v]) {
        if (to == p)
            continue;
        if (vis[to]) {
            low[v] = min(low[v], tin[to]);
            continue;
        }
        dfs(to, v);
        low[v] = min(low[v], low[to]);
        children++;
        if (tin[v] < low[to])
            bridges++;
        if (tin[v] <= low[to] && p != -1)
            cutpoints.insert(v);
    }
    if (p == -1 && children > 1)
        cutpoints.insert(v);
}

void solve() {
    i32 n, m;
    cin >> n >> m;
    g.resize(n);
    low.resize(n);
    tin.resize(n);
    vis.resize(n);
    for (i32 i = 0; i < m; i++) {
        i32 u, v;
        cin >> u >> v;
        u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }

    for (i32 i = 0; i < n; i++) {
        if (!vis[i])
            dfs(i);
    }

    cout << cutpoints.len() << " " << bridges << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}
