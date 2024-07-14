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
    i32 n, m, k;
    cin >> n >> m >> k;
    for (int i = n; i >= k; i--) {
        cout << i << " ";
    }
    for (int i = m + 1; i < k; i++) {
        cout << i << " ";
    }
    for (int i = 1; i <= m; i++) {
        cout << i << " \n"[i == m];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t = 1;
    cin >> t;
    while (t--) solve();
}
