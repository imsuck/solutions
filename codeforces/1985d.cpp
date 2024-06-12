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
    vec<pair<i32, i32>> res(n + 1, {1e9 + 7, 1e9 + 7});
    for (i32 i = 1; i <= n; i++) {
        for (i32 j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c == '#' && res[i].first == 1e9 + 7) res[i].first = j;
            if (c == '#') res[i].second = j;
        }
    }
    i32 mn = 1e9 + 1, x = 0, y = 0;
    for (int i = 1; i <= n; i++) {
        if (res[i].first < mn) {
            mn = res[i].first;
            y = (res[i].first + res[i].second) / 2;
            x = i;
        }
    }
    cout << x << " " << y << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--) solve();
}
