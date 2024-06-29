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

void solve() {
    i32 n, m;
    cin >> n >> m;
    vec<vec<i32>> v(n, vec<i32>(m));
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }
    bool ok = true;
    while (ok) {
        ok = false;
        for (i32 i = 0; i < n; i++) {
            for (i32 j = 0; j < m; j++) {
                i32 prev = v[i][j];
                i32 dx[]{-1, 0, 0, 1}, dy[]{0, -1, 1, 0};
                i32 mx = -1;
                for (i32 k = 0; k < 4; k++) {
                    if (i + dx[k] < 0 || i + dx[k] >= n || j + dy[k] < 0 ||
                        j + dy[k] >= m)
                        continue;
                    mx = max(mx, v[i + dx[k]][j + dy[k]]);
                }
                if (mx < v[i][j]) {
                    v[i][j] = mx;
                }
                ok |= prev != v[i][j];
            }
        }
    }
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < m; j++) {
            cout << v[i][j] << " \n"[j == m - 1];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--)
        solve();
}
