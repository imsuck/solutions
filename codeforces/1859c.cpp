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
    i32 n;
    i64 s = 0, mx = 0;
    cin >> n;
    for (i32 i = 0; i < n; i++) {
        s = 0;
        i64 mx_e = -1;
        for (i64 j = 1, k = 0; j <= n; j++) {
            if (j <= i) {
                s += j * j;
                mx_e = max(mx_e, j * j);
            } else {
                s += (n - k) * j;
                mx_e = max(mx_e, (n - k) * j);
                k++;
            }
        }
        mx = max(mx, s - mx_e);
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
