#include "bits/stdc++.h"
using namespace std;

ostream cnull(nullptr);
#ifndef LOCAL
#define cerr cnull
#endif

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using f32 = float;
using f64 = double;
using f128 = long double;
using str = string;
#define len() size()
#define vec vector
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define pp pop_back
#define eb emplace_back

void solve() {
    i32 n, k;
    cin >> n >> k;
    vec<i64> c(n);
    for (i32 i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (i32 i = 0; i < k; i++) {
        i32 x;
        cin >> x;
        c[x -= 1] = 0;
    }
    vec<i32> g[n], e[n];
    vec<i32> deg(n);
    for (i32 i = 0; i < n; i++) {
        cin >> deg[i];
        e[i].resize(deg[i]);
        for (i32 j = 0; j < deg[i]; j++) {
            cin >> e[i][j];
            g[e[i][j] -= 1].eb(i);
        }
    }
    vec<i32> q;
    for (i32 i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.eb(i);
        }
    }
    for (i32 i = 0; i < (i32)q.len(); i++) {
        for (i32 u : g[q[i]]) {
            deg[u] -= 1;
            if (deg[u] == 0) {
                q.eb(u);
            }
        }
    }
    for (i32 i : q) {
        if (!e[i].empty()) {
            i64 s = 0;
            for (i64 v : e[i]) {
                s += c[v];
            }
            c[i] = min(c[i], s);
        }
    }
    for (i32 i = 0; i < n; i++) {
        cout << c[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
