#include <bits/stdc++.h>
using namespace std;

/*********** template stuff ***********/
#ifndef LOCAL
#define dbg(...)
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
/*********** template stuff ***********/

void solve() {
    i32 n, k;
    cin >> n >> k;
    vec<i32> a(n + 1), h(n + 1), p(n + 1, 0);
    for (i32 i = 1; i <= n; i++) {
        cin >> a[i];
        p[i] = a[i] + p[i - 1];
    }
    for (i32 i = 1; i <= n; i++) {
        cin >> h[i];
    }
    i32 l = 1, r = 1, mx = 0;
    while (r <= n) {
        while (p[r] - p[l - 1] > k) {
            l++;
        }
        if (h[r - 1] % h[r] != 0) {
            l = r;
        }
        if (p[r] - p[l - 1] <= k) {
            mx = max(mx, r - l + 1);
        }
        r++;
    }
    cout << mx << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
