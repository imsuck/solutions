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
    i32 n, k, ans = 0;
    cin >> n >> k;
    if (k >= 30) {
        cout << "0\n";
        return;
    }
    for (i32 i = 1; i <= n; i++) {
        i32 first = i, second = n;
        bool valid = true;
        i32 j;
        for (j = 0; j < k - 2; j++) {
            i32 t = second - first;
            second = first, first = t;
            valid &= first <= second && min(first, second) >= 0;
            if (!valid) {
                break;
            }
        }
        if (valid) {
            ans++;
        }
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
