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
    i32 n, k, c = 0, p = 0;
    cin >> n >> k;
    str s;
    cin >> s;
    bool f = false;
    for (i32 i = 0; i < n; i++) {
        if (s[i] == 'B' && !f) {
            f = true;
            p = i;
            c++;
        }
        if (f && i - p + 1 == k) {
            f = false;
        }
    }
    cout << c << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
