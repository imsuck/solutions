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
    i32 n, mn = 1e9;
    cin >> n;
    i32 a[n];
    for (i32 i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (i32 i = 1; i < n; i++) {
        mn = min(mn, a[i] - a[i - 1]);
        if (mn < 0) {
            mn = -2;
        }
    }
    cout << mn / 2 + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 t;
    cin >> t;
    while (t--)
        solve();
}
