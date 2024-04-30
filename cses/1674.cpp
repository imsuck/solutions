#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
#define vec vector
#define pb push_back

vec<vec<i32>> g;
vec<i32> res;

void dfs(i32 v) {
    for (i32 u : g[v]) {
        dfs(u);
        res[v] += res[u];
    }
    res[v] += g[v].size();
}

void solve() {
    i32 n;
    cin >> n;
    g.resize(n);
    res.resize(n);
    for (i32 i = 1; i < n; i++) {
        i32 v;
        cin >> v;
        g[--v].pb(i);
    }
    dfs(0);
    for (i32 i = 0; i < n; i++) {
        cout << res[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    while (t--)
        solve();
}
