#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;
using str = string;
#define vec vector

void dfs(i32 cur, i32 from, vec<i32> *g, i64 *val) {
    for (i32 i : g[cur]) {
        if (i == from)
            continue;
        dfs(i, cur, g, val);
        val[cur] += val[i];
    }
    val[cur] = max(val[cur], 1LL);
}

void solve() {
    i32 n, q;
    cin >> n;

    vec<i32> g[n + 1];
    vec<bool> vis(n, false);
    i64 val[n + 1];
    fill_n(val, n + 1, 0);

    for (i32 i = 1; i <= n - 1; i++) {
        i32 u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1, g, val);

    cin >> q;
    for (i32 i = 0; i < q; i++) {
        i32 x, y;
        cin >> x >> y;
        cout << val[x] * val[y] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
