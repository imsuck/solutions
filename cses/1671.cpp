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
    vec<vec<pair<i32, i64>>> g(n);
    for (i32 i = 0; i < m; i++) {
        i32 u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
    }
    vec<i64> d(n, 1e18);
    d[0] = 0;
    priority_queue<pair<i64, i32>, vec<pair<i64, i32>>, greater<pair<i64, i32>>> q;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [d_v, v] = q.top();
        q.pop();
        if (d_v != d[v])
            continue;
        for (auto [u, w] : g[v]) {
            if (d[u] > d[v] + w) {
                d[u] = d[v] + w;
                q.emplace(d[u], u);
            }
        }
    }
    for (i32 i = 0; i < n; i++)
        cout << d[i] << " \n"[i == n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    // cin >> t;
    while (t--)
        solve();
}
