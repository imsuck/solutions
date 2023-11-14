#include <bits/stdc++.h>
#include <unistd.h>
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
    i64 n, x;
    cin >> n >> x;
    vec<i64> h(n);
    for (i64 &i : h) {
        cin >> i;
    }
    i64 l = 1, r = 2e9, m;
    while (l < r) {
        m = l + (r - l + 1) / 2;
        i64 s = 0;
        for (i64 i : h) {
            s += max(m - i, i64(0));
        }
        if (s <= x) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
