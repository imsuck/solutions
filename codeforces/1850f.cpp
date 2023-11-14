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
    i32 n, ans = 0;
    cin >> n;
    i32 m[n + 1];
    fill_n(m, n + 1, 0);
    for (i32 i = 1; i <= n; i++) {
        i32 a;
        cin >> a;
        if (a <= n)
            m[a]++;
    }
    for (i32 i = 1; i <= n; i++) {
        i64 cur = 0;
        for (i32 j = 1; j * j <= i; j++) {
            if (i % j == 0) {
                cur += m[j];
                if (i / j != j) {
                    cur += m[i / j];
                }
            }
        }
        ans = max(ans, i32(cur));
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
